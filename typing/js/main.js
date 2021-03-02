 // 사용변수
const GAME_TIME = 9;
let score = 0;
let time = GAME_TIME;
let check_eng = /[a-zA-Z]/;
let isPlaying = false;
let timeInterval;
let words=[];
let checkInterval;
let incorrect=0;
let docFull = document.documentElement;
let audioSuccess = new Audio('Music/Success.mp3');
let audioFail = new Audio('Music/Fail.wav');
let audioIncorrect = new Audio('Music/Incorrect.mp3');
const wordInput = document.querySelector('.word-input');
const wordDisplay = document.querySelector('.word-display');
const wordPreviewDisplay = document.querySelector('.word-preview');
const wordCompletedDisplay = document.querySelector('.word-completed-display');
const scoreDisplay = document.querySelector('.score');
const button = document.querySelector('.button');
const buttonTwo = document.querySelector('.buttonTwo');
const buttonThree = document.querySelector('.buttonThree');
const timeDisplay = document.querySelector('.time');
const processivityDisplay = document.querySelector('.processivity');
const incorrectDisplay = document.querySelector('.incorrect');

swal({
    title: "Hello",
    text: "This game is typing game!",
    icon: "info" //"info,success,warning,error" 중 택1
}); 

function docFullCloseFunction(){
    if (docFull.requestFullscreen){
        docFull.requestFullscreen();
    }else if (docFull.webkitRequestFullscreen){ 
        docFull.webkitRequestFullscreen(); 
    }else if (docFull.mozRequestFullScreen){ 
        docFull.mozRequestFullScreen();
    }else if (docFull.msRequestFullscreen){ 
        docFull.msRequestFullscreen();
    }

    if (document.exitFullscreen){
        document.exitFullscreen();
    }else if (document.webkitExitFullscreen){ 
        document.webkitExitFullscreen();
    }else if (document.mozCancelFullScreen){ 
        document.mozCancelFullScreen();
    }else if (document.msExitFullscreen){ 
        document.msExitFullscreen();
    }
};





function winClose(){
    swal({
        title: "Are you sure?",
        icon: "warning",
        buttons: true,
        dangerMode: true,
      })
      .then((willDelete) => {
        if (willDelete) {
          swal("Poof! Your imaginary file has been deleted!", {
            icon: "success", 
          });window.open('','_self').close();   
        } else {
          swal("Practice!");
        }
      });
   
      
};



function buttonUpSize(a){
    
    a.style.fontSize="22px";
}

function buttonCurrentSize(a){
    
    a.style.fontSize="13.3px";
};
init();

function init(){
    buttonChange('게임로딩중...');
    getWords();
    wordInput.addEventListener('keydown', checkMatch)
};

buttonChange('게임시작');

//게임 실행
function run(){
    
    if(isPlaying)
    {
        return;
    }
    isPlaying=true;
    time = GAME_TIME;
    wordInput.focus();
    scoreDisplay.innerText=0;
    timeInterval = setInterval(countDown, 1000);
    checkInterval = setInterval(checkStatus, 50);
    buttonChange('게임중');
};

function checkStatus(){
    if(!isPlaying && time === 0)
    {
        buttonChange('게임시작');
        clearInterval(checkInterval)
    };
};


function modeChange(){
    if(check_eng.test(wordDisplay.innerText)){
    function run(){ 
        if(isPlaying)
        {
            return;
        };
        isPlaying=true;
        time = GAME_TIME;
        wordInput.focus();
        scoreDisplay.innerText=0;
        timeInterval = setInterval(countDown, 1000);
        checkInterval = setInterval(checkStatus, 50);
        buttonChange('게임중');
    };
    wordDisplay.innerText="강아지";
    run();

    
    words = ['가든', '가람', '가람슬기', '리리', '슬찬','승아', '이루리', '통꽃', '토리', '튼튼', '키클', '틀큰',
              '보아라','수리','가온해', '로지','루다','자랑','자올','타고나','리리','리라','하나','하랑',
              '보예','가이','날애','남','로다','모두가람','모루다','모은','모이','모해','무들','빛솔',
              '봄나','가자','난새','남은','렁찬','마루한','마루나','마루','마디','무지개','빛다','빛초롱',
             '비치나','가장','겨레','나래울','나루해오름','나로','갈','겨울','그린나래','그린','겨슬','겨루']
    
    }else{
        location.reload(true);  
    };
};

function getWords(){//단어 불러오기

    words = ['Hello', 'banana', 'Apple', 'Cherry', 'work','game', 'hard', 'soft', 'pen', 'apple', 'close', 'a','ability',
              'able','about','above', 'accept','according','account','across','act','action','activity','actually','add',
              'address','administration','admit','adult','affect','after','again','against','age','agency','agent','ago',
              'agree','agreement','ahead','air','all','allow','almost','alone','along','already','also','although',
             'always','American','among','amount','analysis','and','animal','another','answer','any','anyone'];
         
    buttonChange('게임시작');  
};



//단어 일치체크
function checkMatch(e) {
if(e.keyCode==13){
    if(wordInput.value.toLowerCase()===wordDisplay.innerText.toLowerCase())
    {
        audioSuccess.play();
        wordInput.value="";
        if(!isPlaying){
            return;
        } 
        score++;
        scoreDisplay.innerText=score;
        time = GAME_TIME;
        const randomIndex = Math.floor(Math.random()*words.length);
        // const randomIndex = 0;
        // wordPreviewDisplay.innerText=words[randomIndex];
        // randomIndex = Math.floor(Math.random()*words.length);
        wordDisplay.innerText = words[randomIndex];   
        processivityDisplay.innerText=Math.floor((score/words.length) * 100);
        
    }
    else if(wordInput.value.toLowerCase()!==wordDisplay.innerText.toLowerCase()){
        audioIncorrect.play();
        incorrect=incorrect+1;    
        incorrectDisplay.innerText=incorrect;
    };
};
};



function countDown(){
     time > 0 ? time-- : isPlaying=false;
     if(!isPlaying)
     {  
         audioFail.play();
          
         alert('game is over your score is ' + scoreDisplay.innerText + 
                 ' your processivity is ' + processivityDisplay.innerText + '% '+
                 'your incorrect is ' + incorrectDisplay.innerText + ' wrong');
         clearInterval(timeInterval);
         location.reload(true);
     }
     timeDisplay.innerText = time;
};

function buttonChange(text){
    button.innerText = text;
    text === '게임시작' ? button.classList.remove('loading') : button.classList.add('loading')
};

