// const calculator = {
//     plus : function(a, b) {
//         return a+b;
//     },
//     minus : function(a, b) {
//         return a-b;
//     },
//     multifly : function(a, b){
//         return a*b;
//     },
//     divide : function(a, b){
//         return a/b;
//     }
// }

// let a = calculator.plus(5, 5);
// console.log(a);

// let b = calculator.minus(5, 5);
// console.log(b);

// let c = calculator.multifly(5, 5);
// console.log(c);

// let d = calculator.divide(5, 5);
// console.log(d);

// const title = document.querySelector("#title");
// const CLICKED_CLASS = "clicked";

// function handleClick(){
//     const currentClass = title.className;
//     if( currentClass !== CLICKED_CLASS){
//         title.className=CLICKED_CLASS;
//     }
//     else
//     {
//         title.className=""; 
//     }
// }

// const title = document.querySelector("#title");
// const CLICKED_CLASS = "clicked";

// function handleClick(){
     
//    title.classList.toggle(CLICKED_CLASS);
    
// }

// function init()
// {

//     title.addEventListener("click", handleClick);
// }

// init();
// function init()
// {

//     title.addEventListener("click", handleClick);
// }

// init();


// :${seconds<10 ? `0${seconds}`:seconds

const clockContainer = document.querySelector(".js-clock"),
clockTitle = clockContainer.querySelector("h1");

function getTime(){
    const date = new Date();
    const minutes = date.getMinutes();
    const hours = date.getHours();
    // const seconds = date.getSeconds();
    clockTitle.innerText= `${hours < 10 ? `0${hours}`:hours}:${minutes<10? `0${minutes}`:minutes
    }`;
}

function init() {
    getTime();
    setInterval(getTime, 1000);
}

init();