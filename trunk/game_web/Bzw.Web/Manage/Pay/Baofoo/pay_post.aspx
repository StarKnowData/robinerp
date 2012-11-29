<%@ Page Language="C#" AutoEventWireup="true"  Inherits="Bzw.Inhersits.Manage_Pay_Baofoo_pay_post" %>

<html>
<head>
    <title>充值接口-提交信息处理</title>
</head>
<body onload='document.pay.submit()'>
 <!-- onload='document.pay.submit()'-->


    <form name='pay' method="post" action="http://paygate.baofoo.com/PayReceive/payindex.aspx" >
        <input type='hidden' name='MerchantID' value='<%=strMerchantID%>'/>
        <input type='hidden' name='PayID' value='<%=strPayID%>'/>
        <input type='hidden' name='TradeDate' value='<%=strTradeDate%>'/>
        <input type='hidden' name='TransID' value='<%=strTransID%>'/>
        <input type='hidden' name='OrderMoney' value='<%=payMoney%>'/>
        <input type='hidden' name='ProductName' value='<%=strProductName%>'/>
        <input type='hidden' name='Amount' value='<%=strAmount%>'/>
        <input type='hidden' name='ProductLogo' value='<%=strProductLogo%>'/>
        <input type='hidden' name='Username' value='<%=strUsername%>'/>
        <input type='hidden' name='Email' value='<%=strEmail%>'/>
        <input type='hidden' name='Mobile' value='<%=strMobile%>'/>
        <input type='hidden' name='AdditionalInfo' value='<%=strAdditionalInfo%>'/>
        <input type='hidden' name='Merchant_url' value='<%=strMerchant_url%>'/>
        <input type='hidden' name='Return_url' value='<%=strReturn_url%>'/>
        <input type='hidden' name='Md5Sign' value='<%=strMd5Sign%>'/>
        <input type='hidden' name='NoticeType' value='<%=strNoticeType%>'/>
    </form>
</body>
</html>