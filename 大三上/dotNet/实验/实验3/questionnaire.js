/*
	Author: 22920212204392黄勖
	Description: 问卷js
	Email: maoliloveyou@foxmail.com
*/
function checkBox(name) {
	var j=0;
	var checkbox = document.getElementsByName(name);
	for(var i=0; i<checkbox.length;i++) {
		if(checkbox[i].checked) {
			j++;
			break;
		}
	}
	if(j==0) return false;
	return true;
}

function check() {
	var q4 = checkBox("q4");
	if(q4 == false) {
		alert("第4题需要至少选择一个选项！");
		return false;
	}
	
	var q5 = checkBox("q5");
	if(q5 == false ) {
		alert("第5题需要至少选择一个选项！");
		return false;
	}
	
	return true;
}
function getResult() {
	if(check() == false) return;
	var result=0;
	var a=0,b=0,c=0,d=0,e=0;
	var q1=document.getElementsByName("q1");
	var q2=document.getElementsByName("q2");
	var q3=document.getElementsByName("q3");
	var q4=document.getElementsByName("q4");
	var q5=document.getElementsByName("q5");
	for(var i=0;i<q1.length;i++){  //第一题
			if(q1[i].checked){
				if(i==q1.length-1){
					a=5;
				}else{
					a=i+1;
				}
			}
		}
	for(var i=0;i<q2.length;i++){   //第二题
			if(q2[i].checked){
				b=i+1;
			}
		}

	for(var i=0;i<q3.length;i++){  //第三题
			if(q3[i].checked){
				if(i==0){
					c=0;
				}else{
					c=i*2;
				}
			}
		}

	for(var i=0;i<q4.length;i++){  //第四题
			if(q4[i].checked){
				if(i==q4.length-1){
					d=0;
				}else{
					d=d+2;
				}
			}
		}

	for(var i=0;i<q5.length;i++){  //第五题
			if(q5[i].checked){
				if(i==q5.length-1){
					e=0;
				}else{
					e=e+2;
				}
			}
			}
	result=a+b+c+d+e;
	if(result<18){
		alert("感谢您的填写，您的测评成绩是："+result+"-----等级：普通！！！（仅做js测试）");
	}else if(result<=27){
		alert("感谢您的填写，您的测评成绩是："+result+"-----等级：良！！！（仅做js测试）");
	}else{
		alert("感谢您的填写，您的测评成绩是："+result+"-----等级：优！！！（仅做js测试）");
	}

}
