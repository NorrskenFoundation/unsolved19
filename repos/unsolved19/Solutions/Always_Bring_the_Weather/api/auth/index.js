
import jwt from 'jsonwebtoken'
import { Router } from 'express'

const router = Router()

export const requireAuth = (req, res, next) => {
    if (req.authenticated) {
        return next()
    }

    res.status(401)
    res.json({ error: 'login required' })
}

export const checkAuth = (req, res, next) => {
    try {
        let token
        // get token form auth header or query string
        if (req.headers.authorization) {
            token = req.headers.authorization.split(" ")[1]
        } else if (req.query.token) {
            token = req.query.token
        }
        if (token) {

            jwt.verify(token, process.env.JWT_SECRET, (err, payload) => {
                if (payload) {
                    req.authenticated = true
                    next()
                } else {
                    next()
                }
            })
        } else {
            next()
        }
    } catch (e) {
        next()
    }
}

router.post('/', (req, res) => {
    const match = req.body.pass === process.env.SECRET
    if (match) {
        const token = jwt.sign('authenticated', process.env.JWT_SECRET)
        res.status(200)
        res.json({ token })
    } else {
        res.status(400)
        res.json({ message: 'Invalid password' })
    }
})

router.get('/', requireAuth, (req, res) => {
    res.status(200).send()
})

export default router