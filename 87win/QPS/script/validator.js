function isEmail(s)
{
 var patrn=/^\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$/;
 if (!patrn.exec(s)){
  return false;
 }else{
  return true;
 }
}
//数字
function isDigit(s)
{
 var patrn=/^[0-9]*$/;
 if (!patrn.exec(s)){
  return false;
 }else{
   return true;
 }
}
//中文
function isChinaText(s)
{
 var patrn=/^[\u4E00-\u9FA5]+$/;
 if (!patrn.exec(s)){
  return false;
 }else{
   return true;
 }
}
//手机号码
function isMobile(s)
{
 var patrn=/^(13[0-9]|15[0|3|6|7|8|9]|18[8|9])\d{8}$$/;
 if (!patrn.exec(s)){
  return false;
 }else{
   return true;
 }
}
//IP
function isIP(s)
{
 var patrn=/^[0-9]{1,3}[.]{1}[0-9]{1,3}[.]{1}[0-9]{1,3}[.]{1}[0-9]{1,3}$/;
 if (!patrn.exec(s)){
 return false;
 }else{
   return true;
 }
}
//电话号码
function isPhoto(s)
{
 var patrn=/^((\(\d{2,3}\))|(\d{3}\-))?(\(0\d{2,3}\)|0\d{2,3}-)?[1-9]\d{6,7}(\-\d{1,4})?$/;
 if (!patrn.exec(s)){
  return false;
 }else{
   return true;
 }
}
//身份证号
function isIdentityCard(s)
{
 var patrn=/^\d{17}[\d|X]|\d{15}$/;
 if (!patrn.exec(s)){
  return false;
 }else{
   return true;
 }
}
//邮政编码
function isPostCode(s)
{
 var patrn=/^(\d{3})(\.\d{4})?$/;
 if (!patrn.exec(s)){
  return false;
 }else{
  return true;
 }
}
