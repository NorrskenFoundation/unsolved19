const app = require('./config/express');

// listen to requests
app.listen('8001', (err) => {
	if (err) {
		return err;
	}
});
/**
 * Exports express
 * @public
 */

module.exports = app;
