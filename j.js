let valueOne = prompt('Введите первое число:') 
let valueTwo = prompt('Введите второе число:') 
 
let operation = prompt('Выберите операцию:') 
 
let dictionary = ['Сложение', 'Вычитание', 'Умножение', 'Деление',] 
 
function comparison() { 
  switch(dictionary) { 
    case 'Сложение' in dictionary: 
      break; 
     
    case 'Вычитание' in dictionary:  
      break; 
 
    case 'Умножение' in dictionary:  
      break; 
     
    case 'Деление' in dictionary:   
      break; 
 
    default: 
      alert(' Вы ввели то, чего не ожидалось. Введите "Сложение", "Вычитание", "Умножение" или "Деление" ') 
  } 
} 
 
comparison() 
 
function result() { 
  if (operation === 'Сложение') { 
    alert (valueOne + valueTwo) 
  }  
  else if (operation === 'Вычитание') { 
    alert (valueOne - valueTwo) 
  }  
  else if (operation === 'Умножение') { 
    alert (valueOne * valueTwo) 
  }  
  else if (operation === 'Деление') { 
    alert (valueOne / valueTwo) 
  } 
} 
 
result()