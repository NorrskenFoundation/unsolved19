
// var form = document.getElementById('chat');
// form.onsubmit = function(event) {
//   event.preventDefault();
//   var para = document.createElement('P');
//   para.classList.add("box");
//   para.classList.add("sd1");
//   para.innerHTML = form.askAway.value;
//   document.getElementById('msgBox').appendChild(para);
//   this.reset();
// };


var question = ["Sorry can I help you something else?", "Can you say that again.", "Do you want me to call an doctor?", "I don't understand", "Hi! I'm your doctor. Please describe your situation for me."];
var expression = ["hello", "sick", "mood", "puke", "eat", "headache", "food", "doctor"];

var form = document.getElementById('chat');
form.onsubmit = function(event) {
  event.preventDefault();
  var para = document.createElement('P');
  var para2 = document.createElement('P');
  para.classList.add("box");
  para2.classList.add("box2");
  para2.innerHTML = form.askAway.value;
  console.log(form.askAway.value);
  document.getElementById('msgBox').appendChild(para2);

  var str = form.askAway.value;
  var index = searchWord(str);
  console.log(index);
  var newStr = getSentence(index);

  para.innerHTML = newStr;
  document.getElementById('msgBox').appendChild(para);
  this.reset();
};

function searchWord(str){
  for(i=0; i<expression.length; i++){
    var num =str.search(expression[i]);
    console.log(num);
    if(num >= 0){
      return i;
    }
    if(i==7){
      return -1;
    }
  }
};

function getSentence(i){
  var min=0;
  var max=5;
  var random = Math.floor(Math.random() * (+max - +min)) + +min;
  console.log(random);
  var text;

  switch (i) {
    case -1:
      text = question[random];
      break;
    case 0:
      text = "Hello! What can I help you with?";
      break;
    case 1:
      text = "How sick do you feel?";
      break;
    case 2:
      text = "Please describe your mood in 3 words for me.";
      break;
    case 3:
      text = "What did you eat during the day?";
      break;
    case 4:
      text = "Do you have an allergic reaction?";
      break;
    case 5:
      text = "Try an take an alvedon";
      break;
    case 6:
      text = "What did you eat during the day?";
      break;
    case 7:
      text = "I'll contact a doctor right away!";
      break;
    default: "eh";
  }
  return text;
};
