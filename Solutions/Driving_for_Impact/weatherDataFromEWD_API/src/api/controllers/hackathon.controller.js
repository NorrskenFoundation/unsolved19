const httpStatus = require('http-status');
const hackathonService = require('../services/hackathon.service');

exports.getData = async (req, res, next) => {
	try {
		const response = hackathonService.getData();
		res.status(httpStatus.OK).json(response);
	} catch (e) {
		next(e);
	}
};
