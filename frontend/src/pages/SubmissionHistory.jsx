import { useEffect, useState } from 'react'
import axios from 'axios'
import {
  ChevronLeft,
  Code2,
  CheckCircle2,
  XCircle,
  Clock,
  AlertTriangle,
  Loader2
} from 'lucide-react'

const API = 'http://localhost:5000/api'

export default function SubmissionHistory({ goBack }) {
  const [submissions, setSubmissions] = useState([])
  const [selected, setSelected] = useState(null)
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState('')
  const [filter, setFilter] = useState('ALL')

  const token = localStorage.getItem('token')

  useEffect(() => {
    if (!token) {
      setError('Please log in to view your submissions.')
      setLoading(false)
      return
    }

    axios.get(`${API}/submissions`, {
      headers: {
        Authorization: `Bearer ${token}`
      }
    })
      .then(res => setSubmissions(res.data.submissions || []))
      .catch(err => {
        setError(err.response?.data?.message || 'Unable to load submissions')
      })
      .finally(() => setLoading(false))
  }, [token])

  async function openSubmission(id) {
    try {
      const res = await axios.get(`${API}/submissions/${id}`, {
        headers: {
          Authorization: `Bearer ${token}`
        }
      })
      setSelected(res.data.submission)
      setError('')
    } catch (err) {
      setError(err.response?.data?.message || 'Unable to load submission details')
    }
  }

  function getColor(verdict) {
    if (verdict === 'ACCEPTED' || verdict === 'AC')
      return '#4ade80'
    if (verdict === 'WA')
      return '#f87171'
    if (verdict?.includes('TIME_LIMIT'))
      return '#fbbf24'
    if (verdict?.includes('RUNTIME'))
      return '#fb923c'
    return '#a78bfa'
  }

  function getIcon(verdict) {
    if (verdict === 'ACCEPTED' || verdict === 'AC')
      return <CheckCircle2 size={17} />
    if (verdict === 'WA')
      return <XCircle size={17} />
    if (verdict?.includes('TIME_LIMIT'))
      return <Clock size={17} />
    return <AlertTriangle size={17} />
  }

  const filtered = submissions.filter(item => {
    if (filter === 'ALL') return true
    if (filter === 'AC') return item.verdict === 'ACCEPTED'
    if (filter === 'WA') return item.verdict === 'WA'
    return !['ACCEPTED', 'WA'].includes(item.verdict)
  })

  if (selected) {
    return (
      <div style={styles.page}>
        <button style={styles.back} onClick={() => setSelected(null)}>
          <ChevronLeft size={18} /> Back to Submissions
        </button>

        <div style={styles.detailCard}>
          <h1>{selected.problemTitle}</h1>
          <p style={styles.muted}>Problem {selected.problemId}</p>

          <div style={{
            ...styles.verdict,
            color: getColor(selected.verdict)
          }}>
            {getIcon(selected.verdict)}
            {selected.verdict.replaceAll('_', ' ')}
          </div>

          <div style={styles.stats}>
            <div>
              <strong>{selected.passed}/{selected.total}</strong>
              <span>Tests passed</span>
            </div>
            <div>
              <strong>{selected.duration}s</strong>
              <span>Duration</span>
            </div>
            <div>
              <strong>{selected.language}</strong>
              <span>Language</span>
            </div>
          </div>

          <h3>Submitted Code</h3>
          <pre style={styles.code}>{selected.code}</pre>

          <h3>Test Case Results</h3>

          {selected.testCases?.map(test => (
            <div key={test.testNumber} style={styles.testRow}>
              <span>Test {test.testNumber}</span>
              <span style={{ color: getColor(test.verdict) }}>
                {test.verdict}
              </span>
            </div>
          ))}

          <details style={{ marginTop: 20 }}>
            <summary style={{ cursor: 'pointer', color: '#a78bfa' }}>
              View complete judge output
            </summary>
            <pre style={styles.code}>{selected.output}</pre>
          </details>

          {selected.errors && (
            <>
              <h3>Error Output</h3>
              <pre style={styles.code}>{selected.errors}</pre>
            </>
          )}
        </div>
      </div>
    )
  }

  return (
    <div style={styles.page}>
      <button style={styles.back} onClick={goBack}>
        <ChevronLeft size={18} /> Back to Home
      </button>

      <div style={styles.heading}>
        <div style={styles.logo}>
          <Code2 size={28} color="#a78bfa" />
          <h1>Submission History</h1>
        </div>
        <p style={styles.muted}>
          Track your coding attempts and previous verdicts.
        </p>
      </div>

      <div style={styles.filters}>
        {['ALL', 'AC', 'WA', 'OTHER'].map(item => (
          <button
            key={item}
            onClick={() => setFilter(item)}
            style={{
              ...styles.filter,
              background: filter === item ? '#7138e8' : '#191925'
            }}
          >
            {item === 'ALL' ? 'All' :
              item === 'AC' ? 'Accepted' :
                item === 'WA' ? 'Wrong Answer' : 'Other'}
          </button>
        ))}
      </div>

      {error && <p style={{ color: '#f87171' }}>{error}</p>}

      <div style={styles.table}>
        <div style={styles.tableHead}>
          <span>SUBMISSION</span>
          <span>PROBLEM</span>
          <span>VERDICT</span>
          <span>LANGUAGE</span>
          <span>TIME</span>
          <span>DATE</span>
        </div>

        {loading && (
          <div style={styles.empty}>
            <Loader2 size={20} /> Loading submissions...
          </div>
        )}

        {!loading && filtered.map(item => (
          <div
            key={item.submissionId}
            style={styles.tableRow}
            onClick={() => openSubmission(item.submissionId)}
          >
            <span style={{ color: '#a78bfa' }}>
              {item.submissionId.slice(0, 8)}
            </span>

            <span>
              <strong>{item.problemTitle}</strong>
              <small>{item.problemId}</small>
            </span>

            <span style={{
              ...styles.verdict,
              color: getColor(item.verdict),
              margin: 0
            }}>
              {getIcon(item.verdict)}
              {item.verdict.replaceAll('_', ' ')}
            </span>

            <span>{item.language}</span>
            <span>{item.duration}s</span>
            <span>{new Date(item.timestamp).toLocaleString()}</span>
          </div>
        ))}

        {!loading && filtered.length === 0 && !error && (
          <div style={styles.empty}>No submissions found.</div>
        )}
      </div>

      <p style={styles.footer}>
        Showing {filtered.length} of {submissions.length} submissions
      </p>
    </div>
  )
}

const styles = {
  page: {
    minHeight: '100vh',
    background: '#090910',
    color: '#eeeef5',
    padding: '35px 5%'
  },
  back: {
    display: 'flex',
    alignItems: 'center',
    gap: 8,
    background: 'none',
    border: 'none',
    color: '#a78bfa',
    cursor: 'pointer',
    marginBottom: 30,
    fontSize: 15
  },
  heading: {
    marginBottom: 30
  },
  logo: {
    display: 'flex',
    alignItems: 'center',
    gap: 12
  },
  muted: {
    color: '#92929f',
    marginTop: 8
  },
  filters: {
    display: 'flex',
    gap: 10,
    flexWrap: 'wrap',
    marginBottom: 20
  },
  filter: {
    padding: '10px 18px',
    border: '1px solid #292936',
    borderRadius: 8,
    color: 'white',
    cursor: 'pointer'
  },
  table: {
    border: '1px solid #292936',
    borderRadius: 12,
    overflowX: 'auto',
    background: '#101019'
  },
  tableHead: {
    display: 'grid',
    gridTemplateColumns: '1.1fr 1.5fr 1.5fr 0.8fr 0.6fr 1.5fr',
    minWidth: 850,
    padding: 18,
    color: '#92929f',
    fontSize: 11,
    fontWeight: 700,
    borderBottom: '1px solid #292936'
  },
  tableRow: {
    display: 'grid',
    gridTemplateColumns: '1.1fr 1.5fr 1.5fr 0.8fr 0.6fr 1.5fr',
    minWidth: 850,
    padding: 18,
    alignItems: 'center',
    borderBottom: '1px solid #292936',
    cursor: 'pointer',
    fontSize: 13
  },
  verdict: {
    display: 'flex',
    alignItems: 'center',
    gap: 7,
    fontWeight: 700,
    fontSize: 13,
    margin: '18px 0'
  },
  empty: {
    padding: 40,
    textAlign: 'center',
    color: '#92929f'
  },
  footer: {
    color: '#92929f',
    marginTop: 20,
    fontSize: 13
  },
  detailCard: {
    maxWidth: 1000,
    margin: '0 auto',
    background: '#101019',
    border: '1px solid #292936',
    borderRadius: 12,
    padding: 25
  },
  stats: {
    display: 'grid',
    gridTemplateColumns: 'repeat(auto-fit,minmax(150px,1fr))',
    gap: 15,
    margin: '25px 0'
  },
  testRow: {
    display: 'flex',
    justifyContent: 'space-between',
    padding: 13,
    borderBottom: '1px solid #292936'
  },
  code: {
    background: '#191925',
    padding: 20,
    borderRadius: 8,
    overflowX: 'auto',
    whiteSpace: 'pre-wrap',
    overflowWrap: 'anywhere',
    color: '#c4b5fd',
    fontSize: 13,
    lineHeight: 1.7
  }
}
