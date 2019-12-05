import React, { useState, useEffect } from 'react'

import checkAuth from '../checkAuth'

const Login = ({ history }) => {
    const [password, setPassword] = useState('')

    useEffect(() => {
        checkAuth(history, () => {
            history.push('/')
        })
    }, [history])

    const login = async (e) => {
        e.preventDefault()
        try {
            const res = await (await fetch('/auth', {
                method: "POST",
                // mode: "cors",
                cache: "no-cache",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify({ "pass": password }),
            })).json()

            if (res.token) {
                console.log('setting token', res.token)
                localStorage.setItem('token', res.token)
                console.log(localStorage.getItem('token'))
                history.push('/')
                return true
            } else {
                localStorage.setItem('token', '')
                setPassword('')
                return false
            }
        } catch (error) {
            localStorage.setItem('token', '')
            setPassword('')
            return false
        }
    }

    return (
        <div className="App">
            <div className="login">
                <form onSubmit={login}>
                    <div className={password.length > 0 ? 'highlight active' : 'highlight'}>
                        <input onChange={(e) => setPassword(e.target.value)} type="password" value={password} autoFocus={true} />
                    </div>
                </form>
            </div>
        </div>
    )
}

export default Login