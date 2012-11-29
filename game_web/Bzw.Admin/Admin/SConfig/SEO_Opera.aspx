<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_SEO_Opera" Codebehind="SEO_Opera.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td colspan="4" class="title_03">
					<strong>SEO内容配置</strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="http://baike.baidu.com/view/1047.htm?fr=ala0" target="_blank">什么是SEO？到百度百科看看吧</a></td>
			</tr>
			<tr style="font-weight: bold;">
				<td align="center">
					页面名称</td>
				<td>
					页面标题</td>
				<td style="width: 265px">
					页面关键字（限500个字符）
				</td>
				<td>
					页面描述（限500个字符）</td>
			</tr>
			<tr>
				<td align="center">
					默认配置
				</td>
				<td>
					<asp:TextBox ID="txtTitle_Default" TextMode="MultiLine" Height="45px" Width="200px" runat="server"></asp:TextBox>
				</td>
				<td style="width: 265px" align="right">
					<asp:TextBox ID="txtKey_Default" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
				<td>
					<asp:TextBox ID="txtDesc_Default" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr>
				<td align="center">
					网站首页
				</td>
				<td>
					<asp:TextBox ID="txtTitle_Index" TextMode="MultiLine" Height="45px" Width="200px" runat="server"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_index" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_index" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr>
				<td align="center">
					注册页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_Reg" TextMode="MultiLine" Height="45px" Width="200px" runat="server"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_Reg" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_Reg" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr>
				<td align="center">
					下载页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_Down" TextMode="MultiLine" Height="45px" Width="200px" runat="server"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_Down" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_Down" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr>
				<td align="center">
					游戏介绍页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_GameInfo" TextMode="MultiLine" Height="45px" Width="200px" runat="server"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_GameInfo" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_GameInfo" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr>
				<td align="center">
					帐号充值页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_Pay" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_Pay" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_Pay" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			

			<tr>
				<td align="center">
					新闻中心页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_NewsList" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_NewsList" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_NewsList" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
		    <tr>
				<td align="center">
				 道具购买页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_PropList" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_PropList" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_PropList" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>

			<tr>
				<td align="center">
					兑奖中心页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_Prize" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_Prize" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_Prize" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			

						<tr>
				<td align="center">
					玩家靓照页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_UserPicture" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_UserPicture" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_UserPicture" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			
			<tr>
				<td align="center">
					客服中心页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_FAQ" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_FAQ" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_FAQ" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			
	
			
			<tr style="display:none;">
				<td align="center">
					网银在线充值页面&nbsp;</td>
				<td>
					<asp:TextBox ID="txtTitle_NetPay" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_NetPay" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_NetPay" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr style="display:none;">
				<td align="center">
					支付宝充值页面&nbsp;</td>
				<td>
					<asp:TextBox ID="txtTitle_AliPay" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_AliPay" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_AliPay" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr style="display:none;">
				<td align="center">
					快钱神州行充值页面&nbsp;</td>
				<td>
					<asp:TextBox ID="txtTitle_KuaiQian" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_KuaiQian" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_KuaiQian" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr style="display:none;">
				<td align="center">
					斗地主总奖牌排行榜页面&nbsp;</td>
				<td>
					<asp:TextBox ID="txtTitle_TotalPrize" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_TotalPrize" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_TotalPrize" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr style="display:none;">
				<td align="center">
					斗地主排行记录列表页面&nbsp;</td>
				<td>
					<asp:TextBox ID="txtTitle_DDZRank" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_DDZRank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_DDZRank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			
			
	
			<tr>
				<td align="center">
					财富排行榜页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_WalletRank" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_WalletRank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_WalletRank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			
			<tr >
				<td align="center">
					混战排行榜页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_Rank" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_Rank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_Rank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
				<tr >
				<td align="center">
					魅力排行榜页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_PrizeRank" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_PrizeRank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_PrizeRank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
		
			
			<tr >
				<td align="center">
					在线时间排行榜页面
				</td>
				<td>
					<asp:TextBox ID="txtTitle_RankDetail" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_RankDetail" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_RankDetail" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			
					<tr>
				<td align="center">
					游戏时间排行榜页面</td>
				<td>
					<asp:TextBox ID="txtTitle_NNTotalRank" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_NNTotalRank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_NNTotalRank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr>
				<td align="center">
					积分排行榜页面&nbsp;</td>
				<td>
					<asp:TextBox ID="txtTitle_NNRank" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_NNRank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_NNRank" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr style="display:none;">
				<td align="center">
					推广员页面
				</td>
				<td>
					<asp:TextBox ID="txtTile_Promoter" runat="server" Height="45px" TextMode="MultiLine" Width="200px"></asp:TextBox></td>
				<td align="right" style="width: 265px">
					<asp:TextBox ID="txtKey_Promoter" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox></td>
				<td align="left">
					<asp:TextBox ID="txtDesc_Promoter" runat="server" Height="45px" TextMode="MultiLine" Width="250px"></asp:TextBox>
				</td>
			</tr>
			<tr>
				<td colspan="4" align="center">
					<asp:Button ID="Button1" runat="server" Text=" 提 交 " class="put" OnClick="EditFilt" />
					&nbsp;&nbsp;<asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
				</td>
			</tr>
	
			<tr>
				<td colspan="4" style="padding-left: 20px;">
					例如：<br />
					页面关键字：网络棋牌游戏，麻将，斗地主，双扣,休闲游戏,电子竞技,游戏下载<br />
					页面描述：提供网络棋牌，对战，休闲等在线游戏的综合网络休闲娱乐平台.包括游戏下载<br />
					搜索引擎能找到页面上的这两种描述，并显示在搜索结果列表中。
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
