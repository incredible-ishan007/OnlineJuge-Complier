import { useState } from 'react'
import axios from 'axios'
import Editor from '@monaco-editor/react'
import {
  Play,
  Send,
  ChevronLeft,
  Loader2,
  CheckCircle2,
  XCircle,
  Clock,
  AlertTriangle
} from 'lucide-react'

const API = 'http://localhost:5000/api'

export default function ProblemPage({ problem, goBack }) {
  const [code, setCode] = useState(`#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}`)
  const [result, setResult] = useState(null)
  const [loading, setLoading] = useState(false)

  async function submitCode() {
    if (loading) return

    const token = localStorage.getItem('token')

    if (!token) {
      setResult({
        verdict: 'ERROR',
        output: 'Please log in before submitting code.',
        errors: ''
      })
      return
    }

    setLoading(true)
    setResult(null)

    const start = performance.now()

    try {
      const res = await axios.post(
        `${API}/submissions/submit`,
        {
          problemId: problem.id,
          code
        },
        {
          timeout: 180000,
          headers: {
            Authorization: `Bearer ${token}`
          }
        }
      )

      setResult({
        ...res.data,
        duration: ((performance.now() - start) / 1000).toFixed(2)
      })

    } catch (err) {
      setResult({
        verdict: 'ERROR',
        output: err.response?.data?.message || err.message,
        errors: ''
      })
    } finally {
      setLoading(false)
    }
  }

  const output = String(result?.output || '')

  const testCases = [
    ...output.matchAll(/Test\s+(\d+)\s*:\s*([A-Z_]+)/g)
  ].map(match => ({
    id: match[1],
    status: match[2]
  }))

  const passed = testCases.filter(t => t.status === 'AC').length
  const total = testCases.length

  const verdict = result?.verdict || ''

  const accepted = verdict === 'ACCEPTED'
  const color = accepted ? '#4ade80' : '#f87171'

  return (
    <div className="solve-page">

      <button className="back-btn" onClick={goBack}>
        <ChevronLeft size={18} />
        Back to Problems
      </button>

      <div className="solve-layout">

        <section className="statement">

          <div className="small-title">
            PROBLEM {problem.id}
          </div>

          <h1>{problem.title}</h1>

          <span className={problem.difficulty.toLowerCase()}>
            {problem.difficulty}
          </span>

          <div className="tags">
            {problem.tags?.map(tag => (
              <span key={tag}>{tag}</span>
            ))}
          </div>

          <div className="problem-statement">
            <pre>{problem.statement}</pre>
          </div>

        </section>

        <section className="editor-section">

          <div className="editor-top">
            <span>C++17</span>
            <span>main.cpp</span>
          </div>

          <Editor
            height="65vh"
            language="cpp"
            theme="vs-dark"
            value={code}
            onChange={value => setCode(value || '')}
            options={{
              fontSize: 14,
              minimap: { enabled: false },
              automaticLayout: true,
              padding: { top: 15 },
              scrollBeyondLastLine: false,
              tabSize: 4
            }}
          />

          <div className="editor-actions">

            <button
              className="secondary-btn"
              disabled={loading}
              onClick={submitCode}
            >
              <Play size={16} />
              Run
            </button>

            <button
              className="primary-btn"
              disabled={loading}
              onClick={submitCode}
            >
              {loading
                ? <Loader2 className="spin" size={16} />
                : <Send size={16} />
              }
              {loading ? 'Judging...' : 'Submit'}
            </button>

          </div>

          {loading && (
            <div className="results-panel">
              <Loader2 className="spin" size={25} />
              <h3>Judging your submission...</h3>
              <p>Executing test cases.</p>
            </div>
          )}

          {result && !loading && (

            <div className="results-panel">

              <div className="result-header">

                <div style={{ color }}>
                  {accepted
                    ? <CheckCircle2 size={32} />
                    : <XCircle size={32} />
                  }
                </div>

                <div>
                  <h2 style={{ color }}>
                    {verdict.replaceAll('_', ' ') || 'JUDGE ERROR'}
                  </h2>

                  <p>
                    {accepted
                      ? 'Congratulations! All test cases passed.'
                      : 'Your submission did not pass all test cases.'}
                  </p>
                </div>

              </div>

              <div className="result-stats">

                <div className="result-stat">
                  <CheckCircle2 color="#4ade80" size={22} />
                  <div>
                    <strong>{passed}/{total}</strong>
                    <span>Test cases passed</span>
                  </div>
                </div>

                <div className="result-stat">
                  <Clock color="#a78bfa" size={22} />
                  <div>
                    <strong>{result.duration}s</strong>
                    <span>Submission duration</span>
                  </div>
                </div>

                <div className="result-stat">
                  <AlertTriangle color="#fbbf24" size={22} />
                  <div>
                    <strong>Unavailable</strong>
                    <span>Peak memory</span>
                  </div>
                </div>

              </div>

              <h3 className="test-heading">
                Test Case Results
              </h3>

              <div className="test-list">

                {testCases.map(test => (
                  <div className="test-item" key={test.id}>

                    <span>Test {test.id}</span>

                    <span className={
                      test.status === 'AC' ? 'test-ac' : 'test-fail'
                    }>
                      {test.status === 'AC'
                        ? <CheckCircle2 size={17} />
                        : <XCircle size={17} />
                      }

                      {test.status.replaceAll('_', ' ')}
                    </span>

                  </div>
                ))}

                {total === 0 && (
                  <p className="empty-tests">
                    No individual test results found.
                    Check complete judge output below.
                  </p>
                )}

              </div>

              {result.errors && (
                <div className="compile-output">
                  <h3>Compiler Errors</h3>
                  <pre>{result.errors}</pre>
                </div>
              )}

              <details className="raw-output">
                <summary>View complete judge output</summary>
                <pre>{output}</pre>
              </details>

            </div>
          )}

        </section>

      </div>
    </div>
  )
}
