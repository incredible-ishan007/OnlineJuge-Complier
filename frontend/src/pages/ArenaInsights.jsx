import { useEffect, useState } from 'react'
import axios from 'axios'
import { ArrowLeft, Brain, Target, Trophy, TrendingDown, RefreshCw } from 'lucide-react'

const API = 'http://localhost:5000/api'

export default function ArenaInsights({ goBack }) {
    const [data, setData] = useState(null)
    const [loading, setLoading] = useState(true)
    const [error, setError] = useState('')

    async function loadInsights() {
        setLoading(true)
        setError('')

        try {
            const token = localStorage.getItem('token')

            const res = await axios.get(`${API}/submissions/insights`, {
                headers: {
                    Authorization: `Bearer ${token}`
                }
            })

            setData(res.data)
        } catch (err) {
            setError(
                err.response?.data?.message ||
                'Unable to load your insights'
            )
        } finally {
            setLoading(false)
        }
    }

    useEffect(() => {
        loadInsights()
    }, [])

    return (
        <main className="insights-page">
            <button className="back-btn" onClick={goBack}>
                <ArrowLeft size={16} /> Back to Home
            </button>

            <div className="insights-heading">
                <span className="small-title">YOUR PERSONAL PERFORMANCE</span>
                <h1>Arena Insights</h1>
                <p>Discover your strengths and find the topics that need more practice.</p>
            </div>

            {loading && <p>Loading your insights...</p>}

            {error && (
                <div className="insights-error">
                    <p>{error}</p>
                    <button className="primary-btn" onClick={loadInsights}>
                        Try Again
                    </button>
                </div>
            )}

            {!loading && !error && data && (
                <>
                    <section className="insights-summary">
                        <div className="insights-stat">
                            <span>Total Submissions</span>
                            <strong>{data.totalSubmissions}</strong>
                        </div>

                        <div className="insights-stat">
                            <span>Accepted Submissions</span>
                            <strong>{data.acceptedSubmissions}</strong>
                        </div>

                        <div className="insights-stat">
                            <span>Topics Practiced</span>
                            <strong>{data.topics.length}</strong>
                        </div>
                    </section>

                    <section className="insights-highlights">
                        <div className="insights-highlight">
                            <div className="insights-highlight-icon">
                                <Trophy size={22} />
                            </div>
                            <span>Strongest Topic</span>
                            <h2>{data.strongestTopic?.topic || 'Not enough data'}</h2>
                            <p>
                                {data.strongestTopic
                                    ? `${data.strongestTopic.acceptanceRate}% acceptance rate`
                                    : 'Submit some solutions to get started'}
                            </p>
                        </div>

                        <div className="insights-highlight">
                            <div className="insights-highlight-icon">
                                <TrendingDown size={22} />
                            </div>
                            <span>Needs More Practice</span>
                            <h2>{data.weakestTopic?.topic || 'Not enough data'}</h2>
                            <p>
                                {data.weakestTopic
                                    ? `${data.weakestTopic.acceptanceRate}% acceptance rate`
                                    : 'Your topic performance will appear here'}
                            </p>
                        </div>

                        <div className="insights-highlight">
                            <div className="insights-highlight-icon">
                                <Target size={22} />
                            </div>
                            <span>Recommended Topic</span>
                            <h2>{data.recommendedTopic?.topic || 'Start solving'}</h2>
                            <p>
                                {data.recommendedTopic
                                    ? 'Focus on this topic in your next practice session'
                                    : 'Solve problems to unlock recommendations'}
                            </p>
                        </div>
                    </section>

                    <section className="insights-topics">
                        <div className="insights-section-heading">
                            <div>
                                <span className="small-title">TOPIC BREAKDOWN</span>
                                <h2>Your Weakness Map</h2>
                            </div>
                            <Brain size={26} />
                        </div>

                        {data.topics.length === 0 ? (
                            <div className="insights-empty">
                                <Brain size={36} />
                                <h3>Your map is waiting to be built</h3>
                                <p>Submit solutions to problems with topic tags to see your performance here.</p>
                            </div>
                        ) : (
                            <div className="insights-topic-list">
                                {data.topics.map(item => (
                                    <div className="insights-topic" key={item.topic}>
                                        <div className="insights-topic-top">
                                            <strong>{item.topic}</strong>
                                            <span>{item.acceptanceRate}%</span>
                                        </div>

                                        <div className="insights-progress">
                                            <div
                                                className="insights-progress-fill"
                                                style={{
                                                    width: `${item.acceptanceRate}%`
                                                }}
                                            />
                                        </div>

                                        <div className="insights-topic-details">
                                            <span>
                                                {item.accepted} accepted / {item.attempts} attempts
                                            </span>
                                            <span>
                                                {item.problems} {item.problems === 1 ? 'problem' : 'problems'}
                                            </span>
                                        </div>
                                    </div>
                                ))}
                            </div>
                        )}
                    </section>

                    <button className="insights-refresh" onClick={loadInsights}>
                        <RefreshCw size={16} /> Refresh Insights
                    </button>
                </>
            )}
        </main>
    )
}
