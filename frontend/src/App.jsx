import { useEffect, useState } from 'react'
import axios from 'axios'
import { Code2, Search, History, LogOut, User, ArrowLeft, Brain } from 'lucide-react'
import ProblemPage from './pages/ProblemPage'
import SubmissionHistory from './pages/SubmissionHistory'
import ArenaInsights from './pages/ArenaInsights'
import AuthPage from './pages/AuthPage'
import './index.css'

const API = 'http://localhost:5000/api'

export default function App() {
    const [problems, setProblems] = useState([])
    const [search, setSearch] = useState('')
    const [difficulty, setDifficulty] = useState('All')
    const [topic, setTopic] = useState('All')
    const [selected, setSelected] = useState(null)
    const [page, setPage] = useState('home')
    const [loading, setLoading] = useState(true)
    const [error, setError] = useState('')

    const [user, setUser] = useState(() => {
        try {
            return JSON.parse(localStorage.getItem('user')) || null
        } catch {
            return null
        }
    })

    useEffect(() => {
        axios.get(`${API}/problems`)
            .then(res => setProblems(res.data.problems || []))
            .catch(() => setError('Unable to load problems'))
            .finally(() => setLoading(false))
    }, [])

    async function openProblem(id) {
        try {
            const res = await axios.get(`${API}/problems/${id}`)
            setSelected(res.data.problem)
            setPage('problem')
            window.scrollTo(0, 0)
        } catch {
            alert('Unable to load problem')
        }
    }

    function goHome() {
        setSelected(null)
        setPage('home')
        window.scrollTo(0, 0)
    }

    function goProblems() {
        setSelected(null)
        setPage('problems')
        window.scrollTo(0, 0)
    }

    function goInsights() {
        if (!user) {
            setPage('auth')
            return
        }

        setPage('insights')
        window.scrollTo(0, 0)
    }

    function handleAuth(userData) {
        setUser(userData)
        setPage('home')
        window.scrollTo(0, 0)
    }

    function logout() {
        localStorage.removeItem('token')
        localStorage.removeItem('user')
        setUser(null)
        goHome()
    }

    if (page === 'auth') {
        return <AuthPage onAuth={handleAuth} goBack={goHome} />
    }

    if (page === 'problem' && selected) {
        return <ProblemPage problem={selected} goBack={goProblems} />
    }

    if (page === 'history') {
        if (!user) return <AuthPage onAuth={handleAuth} goBack={goHome} />
        return <SubmissionHistory goBack={goHome} />
    }

    if (page === 'insights') {
        if (!user) return <AuthPage onAuth={handleAuth} goBack={goHome} />
        return <ArenaInsights goBack={goHome} />
    }

    const topics = [...new Set(problems.flatMap(p => p.tags || []))].sort()

    const filtered = problems.filter(p => {
        const matchesSearch =
            p.title?.toLowerCase().includes(search.toLowerCase()) ||
            String(p.id).toLowerCase().includes(search.toLowerCase())

        const matchesDifficulty =
            difficulty === 'All' ||
            p.difficulty?.toLowerCase() === difficulty.toLowerCase()

        const matchesTopic =
            topic === 'All' ||
            p.tags?.some(tag => tag.toLowerCase() === topic.toLowerCase())

        return matchesSearch && matchesDifficulty && matchesTopic
    })

    const easyCount = problems.filter(p => p.difficulty?.toLowerCase() === 'easy').length
    const mediumCount = problems.filter(p => p.difficulty?.toLowerCase() === 'medium').length
    const hardCount = problems.filter(p => p.difficulty?.toLowerCase() === 'hard').length

    return (
        <div className="app">
            <nav className="navbar">
                <div className="logo" onClick={goHome}>
                    <Code2 size={28} />
                    CodeArena
                </div>

                <div className="nav-links">
                    <a href="#" onClick={e => { e.preventDefault(); goHome() }}>Home</a>
                    <a href="#" onClick={e => { e.preventDefault(); goProblems() }}>Problems</a>
                    <a href="#" onClick={e => {
                        e.preventDefault()
                        setPage('history')
                    }}>Submissions</a>
                    <a href="#" onClick={e => {
                        e.preventDefault()
                        goInsights()
                    }}>
                        <Brain size={15} /> Arena Insights
                    </a>
                    <a href="#leaderboard">Leaderboard</a>
                </div>

                <div className="nav-actions">
                    <button className="login" onClick={() => setPage(user ? 'history' : 'auth')}>
                        <History size={16} /> History
                    </button>

                    {user ? (
                        <>
                            <span className="nav-user">
                                <User size={16} /> {user.name}
                            </span>
                            <button className="signup" onClick={logout}>
                                <LogOut size={16} /> Logout
                            </button>
                        </>
                    ) : (
                        <>
                            <button className="login" onClick={() => setPage('auth')}>Login</button>
                            <button className="signup" onClick={() => setPage('auth')}>Sign Up</button>
                        </>
                    )}
                </div>
            </nav>

            {page === 'home' && (
                user ? (
                    <main className="dashboard">
                        <section className="dashboard-welcome">
                            <div>
                                <span className="small-title">YOUR CODING DASHBOARD</span>
                                <h1>Welcome back, {user.name} ??</h1>
                                <p>Ready to solve something challenging today?</p>
                            </div>
                            <button className="primary-btn" onClick={goProblems}>
                                Explore Problems ?
                            </button>
                        </section>

                        <section className="dashboard-stats">
                            <div className="dashboard-stat">
                                <div className="stat-icon">?</div>
                                <div><span>Total Problems</span><h2>{problems.length}</h2></div>
                            </div>
                            <div className="dashboard-stat">
                                <div className="stat-icon">?</div>
                                <div><span>Difficulty Levels</span><h2>3</h2></div>
                            </div>
                            <div className="dashboard-stat">
                                <div className="stat-icon">?</div>
                                <div><span>Challenges Available</span><h2>{problems.length}</h2></div>
                            </div>
                        </section>

                        <section className="daily-challenge">
                            <div>
                                <span className="challenge-label">? PRACTICE ARENA</span>
                                <h2>Your next challenge awaits</h2>
                                <p>Find a problem, write your solution, and sharpen your coding skills.</p>
                                <button className="primary-btn" onClick={goProblems}>
                                    Browse Problems ?
                                </button>
                            </div>
                            <div className="challenge-art"><Code2 size={90} /></div>
                        </section>

                        <section className="dashboard-difficulty">
                            <div className="difficulty-card"><span className="easy">Easy</span><strong>{easyCount}</strong><small>Problems</small></div>
                            <div className="difficulty-card"><span className="medium">Medium</span><strong>{mediumCount}</strong><small>Problems</small></div>
                            <div className="difficulty-card"><span className="hard">Hard</span><strong>{hardCount}</strong><small>Problems</small></div>
                        </section>
                    </main>
                ) : (
                    <section className="hero">
                        <div className="tagline">? YOUR CODING JOURNEY STARTS HERE</div>
                        <h1>Think. Code.<br /><span>Conquer.</span></h1>
                        <p>Sharpen your problem-solving skills, master algorithms and become a better programmer.</p>
                        <div className="hero-buttons">
                            <button className="primary-btn" onClick={goProblems}>Start Solving ?</button>
                            <button className="secondary-btn" onClick={goProblems}>Explore Problems</button>
                        </div>
                        <div className="hero-stats">
                            <div><h2>{problems.length}+</h2><p>Problems</p></div>
                            <div><h2>3</h2><p>Difficulty Levels</p></div>
                            <div><h2>8</h2><p>Possibilities</p></div>
                        </div>
                    </section>
                )
            )}

            {page === 'problems' && (
                <section className="problems problems-page" id="problems">
                    <button className="back-btn" onClick={goHome}>
                        <ArrowLeft size={16} /> Back to Home
                    </button>

                    <div className="problems-page-title">
                        <span className="small-title">PRACTICE ARENA</span>
                        <h1>Problems</h1>
                        <p>Find your next challenge and start coding.</p>
                    </div>

                    <div className="problem-filters">
                        <div className="search-box">
                            <Search size={18} />
                            <input
                                placeholder="Search by name or ID..."
                                value={search}
                                onChange={e => setSearch(e.target.value)}
                            />
                        </div>

                        <select value={difficulty} onChange={e => setDifficulty(e.target.value)}>
                            <option value="All">All Difficulties</option>
                            <option value="Easy">Easy</option>
                            <option value="Medium">Medium</option>
                            <option value="Hard">Hard</option>
                        </select>

                        <select value={topic} onChange={e => setTopic(e.target.value)}>
                            <option value="All">All Topics</option>
                            {topics.map(t => <option key={t} value={t}>{t}</option>)}
                        </select>

                        <button className="reset-filters" onClick={() => {
                            setSearch('')
                            setDifficulty('All')
                            setTopic('All')
                        }}>
                            Reset
                        </button>
                    </div>

                    <div className="filter-result-count">
                        Showing {filtered.length} of {problems.length} problems
                    </div>

                    {loading && <p>Loading problems...</p>}
                    {error && <p>{error}</p>}

                    {!loading && !error && (
                        <div className="problem-table">
                            <div className="table-head">
                                <span>ID</span><span>PROBLEM</span><span>DIFFICULTY</span><span>TAGS</span>
                            </div>

                            {filtered.map(p => (
                                <div className="problem-row clickable" key={p.id} onClick={() => openProblem(p.id)}>
                                    <span>{p.id}</span>
                                    <strong>{p.title}</strong>
                                    <span className={p.difficulty?.toLowerCase()}>{p.difficulty}</span>
                                    <div className="tags">
                                        {p.tags?.map(tag => <span key={tag}>{tag}</span>)}
                                    </div>
                                </div>
                            ))}

                            {filtered.length === 0 && <p className="empty">No problems match these filters.</p>}
                        </div>
                    )}
                </section>
            )}

            <footer id="leaderboard">
                <div className="logo"><Code2 /> CodeArena</div>
                <p>Built for programmers, by programmers.</p>
                <span>© 2026 CodeArena</span>
            </footer>
        </div>
    )
}
