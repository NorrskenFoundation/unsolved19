import React from 'react';


// Takes a string 'rgb(x, y, z)' and an alpha value A
// Returns a string 'rgba(x, y, z, A)'
export const rgbToRGBA = (rgbString, alpha) => {
  const rgbVals = extractRGBAInt(rgbString);
  return `rgba(${rgbVals.r}, ${rgbVals.g}, ${rgbVals.b}, ${alpha})`;
}

export const rgbaToRGB = (rgbaString, bgColor) => {
  const rgbaVals = extractRGBAInt(rgbaString);
  const bgRGBVals = extractRGBAInt(bgColor);

  const calcColor = (c, cAlpha, bgC) => {
     return (1-cAlpha*(bgC/255)+(cAlpha*c/255))*255;
  }
  const red = Math.round(calcColor(rgbaVals.r, rgbaVals.a, bgRGBVals.r));
  const green = Math.round(calcColor(rgbaVals.g, rgbaVals.a, bgRGBVals.g));
  const blue = Math.round(calcColor(rgbaVals.b, rgbaVals.a, bgRGBVals.b));

  return `rgb(${red}, ${green}, ${blue})`;

}

export const extractRGBAInt = (rgbaString) => {
  const rgbaValues = rgbaString.split('(')[1].split(')')[0].split(',');
  const red = parseInt(rgbaValues[0]);
  const green = parseInt(rgbaValues[1]);
  const blue = parseInt(rgbaValues[2]);
  const alpha = rgbaValues.length > 3 ? parseFloat(rgbaValues[3]) : null;

  return {r: red, g: green, b: blue, a: alpha};

}

// This is a custom discrete color scale
// used by the contour map and color bar
const standardColorScale = [
      [0, 'rgb(11,90,169)'], [1/6, 'rgb(11,90,169)'],
      [1/6, 'rgb(105,175,245)'],[2/6, 'rgb(105,175,245)'],
      [2/6, 'rgb(173,222,255)'],[3/6, 'rgb(173,222,255)'],
      [3/6, 'rgb(250,177,177)'],[4/6, 'rgb(250,177,177)'],
      [4/6, 'rgb(243,81,81)'], [5/6, 'rgb(243,81,81)'],
      [5/6, 'rgb(241,33,33)'], [1, 'rgb(241,33,33)'],
];

const colorScaleGray = [
    [0, 'rgb(230,238,255)'], [1/6, 'rgb(230,238,255)'],
    [1/6, 'rgb(204,220,220)'],[2/6, 'rgb(204,220,220)'],
    [2/6, 'rgb(153,165,170)'],[3/6, 'rgb(153,165,170)'],
    [3/6, 'rgb(102,115,120)'],[4/6, 'rgb(102,115,120)'],
    [4/6, 'rgb(51,65,70)'], [5/6, 'rgb(51,65,70)'],
    [5/6, 'rgb(0,15,30)'], [1, 'rgb(0,15,30)'],
];

const Colorbar = ({darkTheme, height, width, opacity, colorScale, maxValue, style, title, textColor}) => {
  opacity = opacity ? opacity : 1;
  colorScale = colorScale ? colorScale : colorScaleGray;
  return (
    <div style={{display: 'flex', width: width, flexDirection: 'row', justifyContent: 'center', alignItems: 'flex-end', color: textColor, ...style}}>
        {colorScale.map((colorValPair, idx) => {
        let diff = 0;
        let lastEl = false;
        if (idx < colorScale.length-1){
          // The colors take up a percentage each of the color bar,
          // calculate the difference between two percentages
          const curPer = colorValPair[0];
          const nextPer= colorScale[idx+1][0];
          diff = nextPer-curPer;
        }
        else {
          lastEl = true;
          diff = 0.05;
        }

        return (
          <div key={`c${idx}`}
            style={{
              display: 'flex',
              flexDirection: 'column',
              alignItems: 'flex-start',
              width: width * diff
              }}
              >
            <div className={darkTheme ? 'colorbar-color-dark' : 'colorbar-color'}
              style={{width: '100%', height: 20,
                  // if last element, don't show any color, only text.
                  // Always normalize color, apply alpha and then convert back to rgb, this makes color look same on any background
                  backgroundColor: lastEl ? 'transparent' : rgbaToRGB(rgbToRGBA(colorValPair[1], opacity), 'rgb(255, 255, 255)'),
                  borderLeft: '1px solid',
                  borderColor: '#3f3f45'}}/>
            <div style={{borderLeft: '1px solid', borderColor: '#3f3f45', paddingLeft: 2}}>
              {(maxValue*colorValPair[0]).toFixed(2)}
            </div>

          </div>
        );
      })}
      <div style={{marginLeft: 10}}>
        {title}
      </div>
    </div>
  );
}

export default Colorbar;
