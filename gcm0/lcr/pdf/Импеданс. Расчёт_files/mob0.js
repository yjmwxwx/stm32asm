	var tem,cur,ii,iii = 0;var re=''; 

$(window).scroll(function () {movemenu2();});
function movemenu2()
 {
var Vmenn1=$("#nav").height();var vside=$("#dir").height();
var Vwin=$(window).height();var Wwin=$(window).width();
var Vdoc = $(document).scrollTop();

var v1=vside - Vwin + 30; var mnn=$("#nav").height();

var aaa=0+'px'; var bbb=iii*11+'px'; 
//$("#show").text("Top = " + Vdoc+'/'+Wwin+'/'+tem+'/'+mnn+'/'+-iii*7+'/'+iii);
$(".men").css({'position':'fixed'});
$("#nav").css({'position':'fixed'});
cur=Vdoc; 
//--------reclama
if(Wwin > 800){
if (Vwin >= vside){$("#dir").css({'position':'fixed'});}
else {
$("#dir").css({'position':'fixed'});
if ($(document).scrollTop() < v1){$("#dir").offset({top:0});}
else if ($(document).scrollTop() >=v1){$("#dir").css({'position':'fixed'});}
	else  {$("#dir").offset({top:0})}
	}
}else {$("#dir").css({'position':'relative'});$("#dir").css({'display':'block'});}	
//---------menu
	if (tem > cur ){re="down";ii++;iii=0;
if(Wwin<680){$("#nav").css({'top':'3px'});}else{$("#nav").css({'top':'1px'});}
	}
	else if (tem < (cur) )	{re="up";iii=iii-1;ii=0;
if(Wwin<680) {$("#nav").css({'top':'-30px'});}else {$("#nav").css({'top':'-20px'});}
	}
tem=cur	;
}