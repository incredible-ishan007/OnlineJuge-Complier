const { spawn } = require('child_process')
const fs = require('fs')
const path = require('path')
const crypto = require('crypto')

const judgePath = path.resolve(__dirname, '../../judge')
const submissionsPath = path.join(judgePath, 'submissions')
const judgeExe = path.join(judgePath, 'judge.exe')
const historyPath = path.join(__dirname, '../data/submissions.json')

let submissionQueue = Promise.resolve()

async function readHistory() {
    try {
        return JSON.parse(
            await fs.promises.readFile(historyPath, 'utf8')
        )
    } catch {
        return []
    }
}

async function saveHistory(history) {
    await fs.promises.mkdir(path.dirname(historyPath), {
        recursive: true
    })

    await fs.promises.writeFile(
        historyPath,
        JSON.stringify(history.slice(0, 500), null, 2)
    )
}

function getVerdict(output) {
    const verdicts = [
        'ACCEPTED',
        'COMPILATION_ERROR',
        'TIME_LIMIT_EXCEEDED',
        'MEMORY_LIMIT_EXCEEDED',
        'RUNTIME_ERROR',
        'CHECKER_ERROR',
        'WA'
    ]

    return verdicts.find(v => output.includes(v)) || 'JUDGE_ERROR'
}

function getTestCases(output) {
    return [...output.matchAll(
        /Test\s+(\d+)\s*:\s*([A-Z_]+)/g
    )].map(match => ({
        testNumber: Number(match[1]),
        verdict: match[2]
    }))
}

function runJudge(problemId, filename) {
    return new Promise((resolve, reject) => {
        const child = spawn(
            judgeExe,
            [problemId, `submissions/${filename}`],
            {
                cwd: judgePath,
                windowsHide: true
            }
        )

        let output = ''
        let errors = ''

        const timeout = setTimeout(() => {
            child.kill()
        }, 180000)

        child.stdout.on('data', data => {
            output += data.toString()
        })

        child.stderr.on('data', data => {
            errors += data.toString()
        })

        child.on('error', error => {
            clearTimeout(timeout)
            reject(error)
        })

        child.on('close', exitCode => {
            clearTimeout(timeout)

            resolve({
                output,
                errors,
                exitCode
            })
        })
    })
}

async function executeSubmission(req, res) {
    const { problemId, code } = req.body

    if (
        !/^\d{3}$/.test(problemId || '') ||
        typeof code !== 'string' ||
        !code.trim()
    ) {
        return res.status(400).json({
            success: false,
            message: 'Invalid problem ID or code'
        })
    }

    const problemPath = path.join(
        judgePath,
        'problems',
        problemId
    )

    if (!fs.existsSync(problemPath)) {
        return res.status(404).json({
            success: false,
            message: 'Problem not found'
        })
    }

    if (!fs.existsSync(judgeExe)) {
        return res.status(500).json({
            success: false,
            message: 'Judge executable not found'
        })
    }

    const submissionId = crypto.randomUUID()
    const filename = `web_${submissionId}.cpp`
    const filePath = path.join(submissionsPath, filename)

    const start = Date.now()

    try {
        await fs.promises.mkdir(submissionsPath, {
            recursive: true
        })

        await fs.promises.writeFile(filePath, code)

        const result = await runJudge(problemId, filename)

        const duration = Number(
            ((Date.now() - start) / 1000).toFixed(2)
        )

        const verdict = getVerdict(result.output)
        const testCases = getTestCases(result.output)

        let title = problemId

        try {
            const metadata = JSON.parse(
                await fs.promises.readFile(
                    path.join(problemPath, 'metadata.json'),
                    'utf8'
                )
            )

            title = metadata.title
        } catch {}

        const submission = {
            submissionId,
            userId: req.user._id.toString(),
            problemId,
            problemTitle: title,
            verdict,
            language: 'C++17',
            code,
            duration,
            testCases,
            passed: testCases.filter(t => t.verdict === 'AC').length,
            total: testCases.length,
            output: result.output,
            errors: result.errors,
            timestamp: new Date().toISOString()
        }

        const history = await readHistory()

        history.unshift(submission)

        await saveHistory(history)

        res.json({
            success: true,
            ...submission
        })

    } catch (error) {
        res.status(500).json({
            success: false,
            message: error.message
        })
    } finally {
        await fs.promises.unlink(filePath).catch(() => {})
    }
}

exports.submitCode = (req, res) => {
    const job = submissionQueue.then(() =>
        executeSubmission(req, res)
    )

    submissionQueue = job.catch(() => {})
}

exports.getSubmissions = async (req, res) => {
    try {
        const history = await readHistory()

        const userSubmissions = history.filter(
            item => item.userId === req.user._id.toString()
        )

        const submissions = userSubmissions.map(
            ({ code, output, errors, ...item }) => item
        )

        res.json({
            success: true,
            count: submissions.length,
            submissions
        })
    } catch (error) {
        res.status(500).json({
            success: false,
            message: error.message
        })
    }
}

exports.getSubmissionById = async (req, res) => {
    try {
        const history = await readHistory()

        const submission = history.find(
            item =>
                item.submissionId === req.params.id &&
                item.userId === req.user._id.toString()
        )

        if (!submission) {
            return res.status(404).json({
                success: false,
                message: 'Submission not found'
            })
        }

        res.json({
            success: true,
            submission
        })
    } catch (error) {
        res.status(500).json({
            success: false,
            message: error.message
        })
    }
}
