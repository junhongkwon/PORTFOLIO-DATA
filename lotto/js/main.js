let resetID = document.querySelector('#resetId');
let resultID = document.querySelector('#resultId');
let num1 = document.querySelector('#enterNumber1');
let num2 = document.querySelector('#enterNumber2');
let num3 = document.querySelector('#enterNumber3');
let num4 = document.querySelector('#enterNumber4');
let num5 = document.querySelector('#enterNumber5');
let num6 = document.querySelector('#enterNumber6');
let myNumberText = document.querySelector('#myNumberText');
let plusId = document.querySelector('#plusId');
let numArray=[];

swal("Hello!", "This is Lotto645! Good Luck!", "info");



function validate(num){
    txt=num;
    if (txt>=1 && txt<=45) {
        return false
    }else{
        swal("Error", "Enter a number between 1 and 45.", "info");
        return false
    }
}
function lottoResultFunction(){
    numArray.push(num1.value , num2.value , num3.value , num4.value , num5.value , num6.value);  

    
    
    if(num1.value==="" ||num2.value==="" ||num3.value==="" ||num4.value==="" ||num5.value==="" ||num6.value===""){
        swal("Error", "Enter a number", "info");
    }else{
        compareNumber(numArray);
    }
    function compareNumber(numArray){
    let count=0;
    console.log(numArray, lottoNumber);

    for(var i=0; i<lottoNumber.length; i++)
       {
          if(lottoNumber.indexOf(Number(numArray[i]))>-1){
             count=count+1;
             }
       }  
       if (count===6){
           lottoResult.textContent="1등입니다!";
       }
       else if(count===5 && numArray.includes(String(bonus))){
           lottoResult.textContent="2등입니다!"
       }
       else if(count===5){
           lottoResult.textContent="3등입니다!"
       }
       else if(count===4){
           lottoResult.textContent="4등입니다!"
       }
       else if(count===3){
           lottoResult.textContent="5등입니다!"
       }
       else{
           lottoResult.textContent="꽝입니다!"
       }   
       myNumberText.value=numArray;  
       num1.value="";
       num2.value="";
       num3.value="";
       num4.value="";
       num5.value="";
       num6.value="";
       
       swal({
        title: "Good job!",
        text: "Your Number and Result " + 
              "\n"+
               myNumberText.value + 
               "\n"+
               lottoResult.textContent,
        icon: "success",
        button: "Exit!",
      });
    }
    numArray=[];
}

resetID.addEventListener('click', function(){
    swal({
        title: "Are you sure want to reset?",
        text: "Once reset, you will not be able to recover this LottoNumber",
        icon: "warning",
        buttons: true,
        dangerMode: true,
      })
      .then((willDelete) => {
        if (willDelete) {     
              location.reload(true);
            swal("Poof! Your LottoNumber has been deleted!", {
            icon: "success",       
          });
        } else {
          swal("Your LottoNumber is safe!");
        }
      });
    
})


var hubo = Array(45).fill().map(function(element, index){
    return index+1;
});

var lottoResult = document.querySelector('#lottoResult');
console.log(hubo);
var shuffle=[];
while(hubo.length>0){
    var goValue = hubo.splice(Math.floor(Math.random()*hubo.length),1)[0];
    shuffle.push(goValue); 
}

console.log(shuffle);
var bonus = shuffle[shuffle.length-1];
var lottoNumber = shuffle.slice(0,6).sort(function(p, c){
    return p-c;
});

console.log('lottoNumber->', lottoNumber, 'bonus->', bonus);
var result = document.querySelector('#result'); 

function ballPainting(number, result){
    var ball = document.createElement('div');
    
    ball.textContent = number;
    if(number>=1 && number<=10){
        ball.style.backgroundColor='red';
    }
    else if(number>=11 && number<=20){
        ball.style.backgroundColor='orange';
    }
    else if(number>=21 && number<=30){
        ball.style.backgroundColor='yellow';
    }
    else if(number>=31 && number<=40){
        ball.style.backgroundColor='blue';
    }
    else{
        ball.style.backgroundColor='green';
    }
    ball.style.display='inline-block';
    ball.style.border='2px solid black';
    ball.style.borderRadius='45px';
    ball.style.width='58px';
    ball.style.height='58px';
    ball.style.textAlign='center';
    ball.style.marginRight='22px';
    ball.style.fontSize='36px';
    
    
    result.appendChild(ball);
}

let doubleSubmitFlag = false;
function doubleSubmitCheck(){
    if(doubleSubmitFlag){
        return doubleSubmitFlag;
    }else{
        doubleSubmitFlag = true;
        return false;
    }
}

function NumberPainting(){

    if(doubleSubmitCheck())return;    
     else
      for(let i=0; i<=5; i++){
        setTimeout(function asyCallBack(){
            ballPainting(lottoNumber[i], result)
        },1000*i + 1000);          
    }
    setTimeout(function asyCallBack(){
        var bonusSquare = document.querySelector('.bonus');
        ballPainting(bonus, bonusSquare);
       },7000);

    //    setTimeout(function(){
    //     location.reload(true);    
    //    }, 60000);
       // setTimeout(function(){ 
       //   plusId.style.display='inline-block';
       // }, 6500);
       //   plusId.style.display='block'
    
}



function buttonUpSize(button){
    button.style.fontSize="15px";
}

function buttonCurrentSize(button){
    button.style.fontSize="13.3px";
}
