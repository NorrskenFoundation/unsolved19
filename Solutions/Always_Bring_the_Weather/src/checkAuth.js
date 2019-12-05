async function checkAuth(history, callback) {
    try {
        const token = localStorage.getItem('token')
        if (token) {
            const res = await fetch('/auth', {
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            })

            if (res.status === 200) {
                callback()
                return true
            }
        }

        history.push('/login')
        return false

    } catch (error) {
        console.error(error)
    }
}

export default checkAuth