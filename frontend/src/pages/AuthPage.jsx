
import { useState } from 'react'

function AuthPage({ onAuth, goBack }) {
    const [mode, setMode] = useState('login')
    const [name, setName] = useState('')
    const [email, setEmail] = useState('')
    const [password, setPassword] = useState('')
    const [showPassword, setShowPassword] = useState(false)
    const [loading, setLoading] = useState(false)
    const [error, setError] = useState('')

    const handleSubmit = async (e) => {
        e.preventDefault()
        setError('')
        setLoading(true)

        try {
            const response = await fetch(
                `http://localhost:5000/api/auth/${mode === 'login' ? 'login' : 'signup'}`,
                {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify(
                        mode === 'login'
                            ? { email, password }
                            : { name, email, password }
                    )
                }
            )

            const data = await response.json()

            if (!response.ok) {
                throw new Error(data.message || 'Something went wrong')
            }

            localStorage.setItem('token', data.token)
            localStorage.setItem('user', JSON.stringify(data.user))

            onAuth(data.user)

        } catch (err) {
            setError(err.message)
        } finally {
            setLoading(false)
        }
    }

    const styles = {
        page: {
            minHeight: '100vh',
            display: 'flex',
            alignItems: 'center',
            justifyContent: 'center',
            background: '#0b1020',
            padding: '24px',
            color: 'white',
            fontFamily: 'Arial, sans-serif'
        },
        card: {
            width: '100%',
            maxWidth: '420px',
            background: '#151c30',
            padding: '35px',
            borderRadius: '16px',
            border: '1px solid #29334d'
        },
        input: {
            width: '100%',
            padding: '13px',
            marginTop: '8px',
            marginBottom: '20px',
            borderRadius: '8px',
            border: '1px solid #39445e',
            background: '#0b1020',
            color: 'white',
            boxSizing: 'border-box',
            fontSize: '15px'
        },
        button: {
            width: '100%',
            padding: '14px',
            background: '#6366f1',
            color: 'white',
            border: 'none',
            borderRadius: '8px',
            fontSize: '16px',
            fontWeight: 'bold',
            cursor: 'pointer'
        }
    }

    return (
        <div style={styles.page}>
            <div style={styles.card}>
                <button
                    onClick={goBack}
                    style={{
                        background: 'none',
                        border: 'none',
                        color: '#a5b4fc',
                        cursor: 'pointer',
                        marginBottom: '20px'
                    }}
                >
                    ← Back to CodeArena
                </button>

                <h1 style={{ textAlign: 'center', marginBottom: '8px' }}>
                    <span style={{ color: '#818cf8' }}>Code</span>Arena
                </h1>

                <p style={{ textAlign: 'center', color: '#9ca3af' }}>
                    {mode === 'login'
                        ? 'Welcome back! Login to continue.'
                        : 'Create your CodeArena account.'}
                </p>

                <div style={{
                    display: 'flex',
                    gap: '10px',
                    margin: '28px 0'
                }}>
                    <button
                        onClick={() => {
                            setMode('login')
                            setError('')
                        }}
                        style={{
                            ...styles.button,
                            background: mode === 'login' ? '#6366f1' : '#29334d'
                        }}
                    >
                        Login
                    </button>

                    <button
                        onClick={() => {
                            setMode('signup')
                            setError('')
                        }}
                        style={{
                            ...styles.button,
                            background: mode === 'signup' ? '#6366f1' : '#29334d'
                        }}
                    >
                        Sign Up
                    </button>
                </div>

                <form onSubmit={handleSubmit}>
                    {mode === 'signup' && (
                        <>
                            <label>Full Name</label>
                            <input
                                style={styles.input}
                                type="text"
                                placeholder="Enter your name"
                                value={name}
                                onChange={(e) => setName(e.target.value)}
                                required
                            />
                        </>
                    )}

                    <label>Email Address</label>
                    <input
                        style={styles.input}
                        type="email"
                        placeholder="Enter your email"
                        value={email}
                        onChange={(e) => setEmail(e.target.value)}
                        required
                    />

                    <label>Password</label>

                    <div style={{ position: 'relative' }}>
                        <input
                            style={{ ...styles.input, paddingRight: '65px' }}
                            type={showPassword ? 'text' : 'password'}
                            placeholder="Enter your password"
                            value={password}
                            onChange={(e) => setPassword(e.target.value)}
                            required
                        />

                        <button
                            type="button"
                            onClick={() => setShowPassword(!showPassword)}
                            style={{
                                position: 'absolute',
                                right: '10px',
                                top: '20px',
                                background: 'none',
                                border: 'none',
                                color: '#a5b4fc',
                                cursor: 'pointer'
                            }}
                        >
                            {showPassword ? 'Hide' : 'Show'}
                        </button>
                    </div>

                    {error && (
                        <p style={{
                            color: '#f87171',
                            fontSize: '14px',
                            marginBottom: '18px'
                        }}>
                            {error}
                        </p>
                    )}

                    <button
                        type="submit"
                        style={{
                            ...styles.button,
                            opacity: loading ? 0.7 : 1
                        }}
                        disabled={loading}
                    >
                        {loading
                            ? 'Please wait...'
                            : mode === 'login'
                                ? 'Login to CodeArena'
                                : 'Create Account'}
                    </button>
                </form>

                <p style={{
                    textAlign: 'center',
                    color: '#9ca3af',
                    fontSize: '13px',
                    marginTop: '25px'
                }}>
                    CodeArena - Practice. Compete. Improve.
                </p>
            </div>
        </div>
    )
}

export default AuthPage
