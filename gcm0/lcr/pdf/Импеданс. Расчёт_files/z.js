function impedance1(obj)
{
var f=obj.ft.value; var fm=obj.fmt.value; var w = 2*Math.PI*f*fm;
var c=obj.ct.value; var cm=obj.cmt.value; var c=c*cm; var xc=1/(w*c);
var l=obj.lt.value; var lm=obj.lmt.value; var l = l*lm; var xl=w*l;
var x = xl-xc;
var r=obj.rt.value; var rm=obj.rmt.value; var r = r*rm;

var z=Math.sqrt(r*r+x*x); 

obj.xzm.value = 'Ohm' ;
if (z>999.999) {var z = z/1000; obj.xzm.value = 'kOhm' }
if (z>999.999) {var z = z/1000; obj.xzm.value = 'MOhm' }
var ok = obj.okr.value; 
var k = 10;
obj.zt.value=rmod(z,ok);

var fi = Math.atan(x/r); obj.fi.value=rmod(fi*180/Math.PI,ok);
var d = Math.atan(r/x); obj.d.value=rmod(d*180/Math.PI,ok);

obj.xlm.value = 'Ohm' 
if (xl>999.999) {var xl = xl/1000; obj.xlm.value = 'kOhm' }
if (xl>999.999) {var xl = xl/1000; obj.xlm.value = 'MOhm' }

obj.xcm.value = 'Ohm' 
if (xc>999.999) {var xc = xc/1000; obj.xcm.value = 'kOhm' }
if (xc>999.999) {var xc = xc/1000; obj.xcm.value = 'MOhm' }

obj.xl.value=rmod(xl,ok); obj.xc.value=rmod(xc,ok);

}
function impedance2(obj) 
{
var f=obj.ft.value; var fm=obj.fmt.value; var w = 2*Math.PI*f*fm;
var c=obj.ct.value; var cm=obj.cmt.value; var c=c*cm; var xc=1/(w*c); var bc = 1/xc;
var l=obj.lt.value; var lm=obj.lmt.value; var l = l*lm; var xl=w*l;     var bl = 1/xl;
var r=obj.rt.value; var rm=obj.rmt.value; var r = r*rm;                 var g = 1/r;
var b = bl-bc;


var y=Math.sqrt(g*g+b*b); var z = 1/y; 

obj.xzm.value = 'Ohm' ;
if (z>999.999) {var z = z/1000; obj.xzm.value = 'kOhm' }
if (z>999.999) {var z = z/1000; obj.xzm.value = 'MOhm' }
var ok = obj.okr.value; 
var k = 10;
obj.zt.value=rmod(z,ok); 

var fi = Math.atan(b/g); obj.fi.value=rmod(fi*180/Math.PI,ok);
var d = Math.atan(g/b); obj.d.value=rmod(d*180/Math.PI,ok);

obj.xlm.value = 'Ohm' 
if (xl>999.999) {var xl = xl/1000; obj.xlm.value = 'kOhm' }
if (xl>999.999) {var xl = xl/1000; obj.xlm.value = 'MOhm' }

obj.xcm.value = 'Ohm' 
if (xc>999.999) {var xc = xc/1000; obj.xcm.value = 'kOhm' }
if (xc>999.999) {var xc = xc/1000; obj.xcm.value = 'MOhm' }
obj.xl.value=rmod(xl,ok); obj.xc.value=rmod(xc,ok);

}
function rmod(value, precision) // Функция округления
{
  var precision_number = Math.pow(10, precision);     // спецчисло для округления
    return Math.round(value * precision_number) / precision_number;
}