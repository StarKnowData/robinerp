<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.PropInfo" %>

<html xmlns="http://www.w3.org/1999/xhtml" >
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <style type="text/css">
    td{font-size:12px}
    body {
	    margin-left: 0px;
	    margin-top: 0px;
	    margin-right: 0px;
	    margin-bottom: 0px;
    }
    </style>
    <script type="text/javascript">
        function switchProp(pid, pname, price, vipprice, desc, price100, vipprice100) {
           
            document.getElementById("propImage").src = "image/PropGif" + pid + ".gif";
            document.getElementById("PropName").innerText = pname;
            document.getElementById("propPrice").innerText = price100;
            document.getElementById("propVipPrice").innerText = vipprice100;
            document.getElementById("propDescript").innerText = desc;
       
           // alert("bzw://prop/change?propid=" + pid + "&price=" + price + "&vipprice=" + vipprice+"&num="+num);
             document.location.replace("bzw://prop/change?propid=" + pid + "&price=" + price + "&vipprice=" + vipprice);
        }
    </script>
</head>
<body scroll="no" style="border:0px;" bgcolor="#<%=GetBgColor()%>"> 
    <table width="100%" border="0" cellpadding="0" cellspacing="0" bgcolor="#CCCCCC">
      <tr>
        <td  bgcolor="#666666"><table width="100%" border="0" cellpadding="0" cellspacing="0"  >
          <tr bgcolor="#<%=GetBgColor()%>">
            <td width=100 rowspan="6" align="center" valign="middle">
                <img id="propImage" src="image/PropGif<%=PropImg%>.gif">
            </td>
 
          </tr>
          <tr bgcolor="#<%=GetBgColor()%>">
          <td height="30"  style="padding-left:3px" >
           
				数量：<%=UserPropCount %>
          </td>
          </tr>
          <tr  bgcolor="#<%=GetBgColor()%>">
            <td height="30"  style="padding-left:3px">
				名称：<span id="propName"><%=PropName%></span></td>
          </tr>
          <tr  bgcolor="#<%=GetBgColor()%>">
            <td height="30"  style="padding-left:3px">
				价格：<span id="propPrice"><%=UiCommon.StringConfig.AddZeros(PropPrice)%></span>&nbsp;&nbsp;&nbsp;&nbsp;VIP会员价格：<span id="propVipPrice"><%=UiCommon.StringConfig.AddZeros(PropVipPrice)%></span></td>
          </tr >
          
          <tr  bgcolor="#<%=GetBgColor()%>">
            <td height="30"  style="padding-left:3px">描述：<span id="propDescript"><%=PropDescript%></span></td>
          </tr>
        </table></td>
      </tr>
    </table>
    <script type="text/javascript">
        var PropID = '<%=PropID %>';
        var PropName = '<%=PropName %>';
        var PropPrice = '<%=PropPrice %>';
        var PropVipPrice = '<%=PropVipPrice %>';
        var PropDescript = '<%=PropDescript %>';
        var PropPrice100 = '<%=UiCommon.StringConfig.AddZeros(PropPrice) %>';
        var PropVipPrice100 = '<%=UiCommon.StringConfig.AddZeros(PropVipPrice) %>';
         
        switchProp(PropID, PropName, PropPrice, PropVipPrice, PropDescript, PropPrice100, PropVipPrice100);
    </script>
</body>
</html>
