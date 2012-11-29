<%@ Page Language="C#" AutoEventWireup="true"  Inherits="Bzw.Inhersits.VipApply" %>
 

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
	 
	     font-size:14px;
	     font-weight:bold;
    }
    </style>
    <script type="text/javascript">
        function switchProp(pid, price, type) {
            //  alert("bzw://prop/change?propid=" + pid + "&price=" + price + "&viptype=" + type);
            document.getElementById("lblMsg").innerHTML = price;

            document.location.replace("bzw://prop/change?propid=" + pid + "&price=" + price + "&viptype=" + type);
        }
    </script>
</head>
<body scroll="no" style="border:0px; " bgcolor="#<%=bgColor %>" > 
 
    <table width="100%" border="0" cellpadding="0" cellspacing="0" style=" margin-top:10px;width:381px;"   bgcolor="#CCCCCC">
      <tr>
        <td bgcolor="#666666" ><table width="100%" border="0" cellpadding="0" cellspacing="0"  >
          <tr  bgcolor="#<%=bgColor %>">
            <td width="100" rowspan="6" align="center" valign="middle">
                <img id="propImage" src="image/PropGif10.gif" width="89px" height="91px">
            </td>

          </tr>
          <tr  bgcolor="#<%=bgColor %>">
            <td  style="padding-left:3px">
				 名称：<span id="propName">VIP会员卡</span></td>
			
          </tr>
          <tr   bgcolor="#<%=bgColor %>">
            <td   style="padding-left:3px">
				类型：<span id="propPrice"><select id="ddlVipType" onchange="changePrice(this.value) ">
				<option value="7">一周VIP</option>
				<option value="30">一月VIP</option>
				<option value="180">半年VIP</option>
				<option value="360">一年VIP</option>
				</select>
				 </span></td>
          </tr >
        <tr  bgcolor="#<%=bgColor %>">
            <td  style="padding-left:3px">
				价格：<span id="propVipPrice">	<asp:Label ID="lblMsg" runat="server"></asp:Label></span></td>
          </tr> 
       
        <tr  bgcolor="#<%=bgColor %>">
            <td    style="padding-left:3px">描述：<span id="propDescript">申请成为VIP会员后，享有在游戏中红色高亮显示昵称、购买所有游戏道具享受最优惠价格、可踢非VIP会员离开游戏
房间的尊贵待遇。
             </span></td>
          </tr> 
        </table></td>
      </tr>
      <tr><td></td></tr>
    </table> 
    <script type="text/javascript">
        var PropID = '9999';

        var PropPrice = '<%=PropPrice %>';

        var PropType = document.getElementById("ddlVipType").value;

        switchProp(PropID, '<%=MoneyToViptimeWeek %>', PropType);
        function changePrice(vtype) {

            if (vtype == "7") {
                switchProp(PropID, '<%=MoneyToViptimeWeek %>', vtype);

            }
            if (vtype == "30") {
                switchProp(PropID, '<%=MoneyToViptimeMonth %>', vtype);

            }
            if (vtype == "180") {
                switchProp(PropID, '<%=MoneyToViptimeHYear %>', vtype);
            }

            if (vtype == "360") {
                switchProp(PropID, '<%=MoneyToViptimeYear %>', vtype);
            }

        }
    </script>
    
</body>

</html>