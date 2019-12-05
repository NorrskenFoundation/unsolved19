const express = require('express');
const routes = require('../api/routes/v1');
/**
 * Express instance
 * @public
 */
const app = express();

/* app.disable('etag'); */

// TODO: Include CSRF middlewares here

// parse body params and attache them to req.body
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// gzip compression

// secure apps by setting various HTTP headers

// This middleware take care of the origin when the origin is undefined.
// origin is undefined when request is local
// ! You might want to remove this in prod
app.use((req, res, next) => {
	req.headers.origin = req.headers.origin || req.headers.host;
	next();
});

// mount api v1 routes
app.use('/v1', routes);

module.exports = app;
