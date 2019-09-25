const express = require('express');

// import all the routes here

const hackathonRoutes = require('./hackathon.route');

const router = express.Router();

/**
 * GET v1/status
 */
router.use('/hackathon', hackathonRoutes);

module.exports = router;
