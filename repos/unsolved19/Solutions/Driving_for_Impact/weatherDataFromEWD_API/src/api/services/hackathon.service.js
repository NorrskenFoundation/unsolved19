const moment = require('moment');
const fs = require('fs');

class HackathonService {
	async getData() {
		const urls = [
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150000?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150015?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150030?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150045?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150100?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150115?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150130?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150145?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150200?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150215?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150230?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150245?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150300?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150315?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150330?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150345?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150400?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150415?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150430?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150445?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150500?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150530?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150515?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150545?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150600?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150630?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150615?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150645?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150700?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150730?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150715?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150730?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150800?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150830?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150815?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150845?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150900?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150930?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150915?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909150945?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151000?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151030?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151015?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151045?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151100?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151130?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151115?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151145?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151200?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151230?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151215?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151245?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151300?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151330?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151315?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151345?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151400?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151430?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151415?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151445?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151500?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151530?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151515?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151545?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151600?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151630?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151615?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151645?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151700?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151730?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151715?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151745?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151800?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151830?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151815?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151845?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151900?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151930?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151915?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909151945?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152000?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152030?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152015?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152045?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152100?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152130?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152115?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152145?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152200?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152230?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152215?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152245?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152300?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152330?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152315?location=stockholm',
			'https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/201909152345?location=stockholm',
		];
		for (let i = 0; i <= urls.length; i += 1) {
			const bearerToken =
				'Bearer eyJ4NXQiOiJOVEF4Wm1NeE5ETXlaRGczTVRVMVpHTTBNekV6T0RKaFpXSTRORE5sWkRVMU9HRmtOakZpTVEiLCJraWQiOiJOVEF4Wm1NeE5ETXlaRGczTVRVMVpHTTBNekV6T0RKaFpXSTRORE5sWkRVMU9HRmtOakZpTVEiLCJhbGciOiJSUzI1NiJ9.eyJzdWIiOiJoYWNrYXRob24udXNlckBtYWlsLmNvbUBjYXJib24uc3VwZXIiLCJhdWQiOiIzY1lkTHlsMmtfeUFIRTd2RGVMSFJGVUdURm9hIiwiYXpwIjoiM2NZZEx5bDJrX3lBSEU3dkRlTEhSRlVHVEZvYSIsInNjb3BlIjoiYXBpbTpzdWJzY3JpYmUiLCJpc3MiOiJodHRwczpcL1wvZGVtby1pcy53ZXN0ZXVyb3BlLmNsb3VkYXBwLmF6dXJlLmNvbVwvb2F1dGgyXC90b2tlbiIsImV4cCI6MTU2OTI0NDM4NSwiaWF0IjoxNTY4NjM5NTg1LCJqdGkiOiIyM2YyM2M2OS03NjE5LTRmZmEtOWI3Yi00ZmU4ZWJjY2MyZTcifQ.av_Ze4XwVsdYAk0yJ2lbYfpS-H1KXGaaZPdOxFtF7eOnGAKAsQhMUSmkmeaKmGruXeGq7po-AlKuh4FlDFZxtIeHZybixI9yVxurM7Fs1F89v8x5b1Cfj1XaezORXt_hvJiycnk0rSVo_PEfykFFND-UMyKe1OroZO09Q-7OKw1Dw5Nqyf6Df2eeeAAg9X5E0jYtteqlL9AbJUBTJSR0QxLkGpRd2gqFiFw82WDvt_4xK6d2C9AIfwN0frVW6jwH1zPsZFIbF2pZ1Rvsg3IiGPD9QpYyGlK5iwkg2pdM4N_ju3sa1P9AmDTidhcHDNcH_o5H0mWDGE9sxtO4LJFZwA';
			// const url = `https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/${time}?location=stockholm`;
			console.log('url is: ', urls[i]);
			const options = {
				method: 'GET',
				headers: {
					'Content-Type': 'application/json',
					Authorization: `Bearer ${bearerToken}`,
				},
			};
			const response = await fetch(urls[i], options);
			const responseParsed = await response.json();
			/* console.log('response', responseParsed); */

			const content = await JSON.stringify(responseParsed);
			console.log('content', content);
			fs.writeFile(`C:/Users/ENTATIR/Documents/EIC-Documents/Norrsken-Hackathon/${i}.json`, content);
		}
	}
}
module.exports = new HackathonService();
