const express = require('express')
const cors = require('cors')
const fs = require('fs')
const path = require('path')
require('dotenv').config()

const connectDB = require('./config/db')
const submissionRoutes = require('./routes/submissionRoutes')
const authRoutes = require('./routes/authRoutes')

const app = express()

app.use(cors())
app.use(express.json())

const problemsPath = path.join(__dirname, '../judge/problems')

// Home API
app.get('/', (req, res) => {
    res.json({
        success: true,
        message: 'CodeArena API is running!'
    })
})

// Authentication routes
app.use('/api/auth', authRoutes)

// Get all problems
app.get('/api/problems', async (req, res) => {
    try {
        const folders = await fs.promises.readdir(problemsPath, {
            withFileTypes: true
        })

        const problems = []

        for (const folder of folders) {
            if (!folder.isDirectory()) continue

            const metadataPath = path.join(
                problemsPath,
                folder.name,
                'metadata.json'
            )

            try {
                const data = await fs.promises.readFile(
                    metadataPath,
                    'utf8'
                )

                problems.push(JSON.parse(data))
            } catch (err) {
                console.log('Skipping:', folder.name)
            }
        }

        problems.sort((a, b) => a.id.localeCompare(b.id))

        res.json({
            success: true,
            count: problems.length,
            problems
        })

    } catch (err) {
        res.status(500).json({
            success: false,
            message: 'Unable to fetch problems',
            error: err.message
        })
    }
})

// Get individual problem
app.get('/api/problems/:id', async (req, res) => {
    try {
        const id = req.params.id

        if (!/^\d{3}$/.test(id)) {
            return res.status(400).json({
                success: false,
                message: 'Invalid problem ID'
            })
        }

        const folderPath = path.join(problemsPath, id)

        const metadataPath = path.join(
            folderPath,
            'metadata.json'
        )

        const statementPath = path.join(
            folderPath,
            'problem.txt'
        )

        const metadata = JSON.parse(
            await fs.promises.readFile(metadataPath, 'utf8')
        )

        const statement = await fs.promises.readFile(
            statementPath,
            'utf8'
        )

        res.json({
            success: true,
            problem: {
                ...metadata,
                statement
            }
        })

    } catch (err) {
        res.status(404).json({
            success: false,
            message: 'Problem not found'
        })
    }
})

// Submission routes
app.use('/api/submissions', submissionRoutes)

// Start server
const PORT = process.env.PORT || 5000

const startServer = async () => {
    await connectDB()

    app.listen(PORT, () => {
        console.log(`CodeArena API running on port ${PORT}`)
    })
}

startServer()