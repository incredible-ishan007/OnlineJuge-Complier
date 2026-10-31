const express = require('express')
const router = express.Router()

const {
    submitCode,
    getSubmissions,
    getSubmissionById
} = require('../controllers/submissionController')

const {
    getInsights
} = require('../controllers/insightsController')

const protect = require('../middleware/authMiddleware')

router.use(protect)

router.get('/insights', getInsights)
router.get('/', getSubmissions)
router.post('/submit', submitCode)
router.get('/:id', getSubmissionById)

module.exports = router
