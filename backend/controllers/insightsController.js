const fs = require('fs')
const path = require('path')

const historyPath = path.join(__dirname, '../data/submissions.json')
const problemsPath = path.resolve(__dirname, '../../judge/problems')

exports.getInsights = async (req, res) => {
    try {
        let history = []

        try {
            history = JSON.parse(
                await fs.promises.readFile(historyPath, 'utf8')
            )
        } catch {}

        const userId = req.user._id.toString()

        const submissions = history.filter(
            item => item.userId === userId
        )

        const metadataCache = new Map()
        const topicStats = {}

        for (const submission of submissions) {
            const problemId = submission.problemId

            if (!metadataCache.has(problemId)) {
                try {
                    const metadataPath = path.join(
                        problemsPath,
                        problemId,
                        'metadata.json'
                    )

                    const metadata = JSON.parse(
                        await fs.promises.readFile(metadataPath, 'utf8')
                    )

                    metadataCache.set(
                        problemId,
                        Array.isArray(metadata.tags) ? metadata.tags : []
                    )
                } catch {
                    metadataCache.set(problemId, [])
                }
            }

            const tags = metadataCache.get(problemId)
            const accepted =
                submission.verdict === 'ACCEPTED' ||
                submission.verdict === 'AC'

            for (const tag of tags) {
                if (!topicStats[tag]) {
                    topicStats[tag] = {
                        topic: tag,
                        attempts: 0,
                        accepted: 0,
                        problems: new Set()
                    }
                }

                topicStats[tag].attempts++

                if (accepted) {
                    topicStats[tag].accepted++
                }

                topicStats[tag].problems.add(problemId)
            }
        }

        const topics = Object.values(topicStats)
            .map(item => ({
                topic: item.topic,
                attempts: item.attempts,
                accepted: item.accepted,
                problems: item.problems.size,
                acceptanceRate: item.attempts
                    ? Math.round(item.accepted / item.attempts * 100)
                    : 0
            }))
            .sort((a, b) => b.attempts - a.attempts)

        const practicedTopics = topics.filter(
            item => item.attempts > 0
        )

        const strongestTopic = [...practicedTopics].sort(
            (a, b) => b.acceptanceRate - a.acceptanceRate
        )[0] || null

        const weakestTopic = [...practicedTopics].sort(
            (a, b) => a.acceptanceRate - b.acceptanceRate
        )[0] || null

        const recommendedTopic = [...practicedTopics].sort(
            (a, b) => a.acceptanceRate - b.acceptanceRate ||
                b.attempts - a.attempts
        )[0] || null

        res.json({
            success: true,
            totalSubmissions: submissions.length,
            acceptedSubmissions: submissions.filter(
                item =>
                    item.verdict === 'ACCEPTED' ||
                    item.verdict === 'AC'
            ).length,
            topics,
            strongestTopic,
            weakestTopic,
            recommendedTopic
        })
    } catch (error) {
        res.status(500).json({
            success: false,
            message: error.message
        })
    }
}
