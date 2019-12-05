const express = require('express');

const controller = require('../../controllers/hackathon.controller');

const router = express.Router();

router.route('/getData').get(controller.getData);
module.exports = router;
