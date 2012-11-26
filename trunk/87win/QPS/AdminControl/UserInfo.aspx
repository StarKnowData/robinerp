<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UserInfo.aspx.cs" Inherits="QPS.Web.AdminControl.UserInfo" %>


<%@ Register assembly="SdCms.Controls" namespace="SdCms.Controls" tagprefix="cc1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>操作人员维护</title>
    <style type="text/css"> BODY { MARGIN: 0px } </style>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    
	<script language="javascript" type="text/javascript" src="../script/Common.js"></script>
	<script language="JavaScript" type="text/JavaScript" src="../script/Modality.js"></script>
</head>

<base target="_self"></base>
<body>
    <form id="form1" runat="server">
    
    <div style="text-align:center;">
    <table width=90% border=0 cellpadding="3">
    <tr>
    <td style="text-align:left; color:Red;">根据姓名和用户名查询:</td>
    </tr>
    </table>
	<table width=90% border=0 cellpadding="3">
	    <tr>
	    
	        <td align=left >输入您要查询的姓名</td>
	        <td  align=left>
                <asp:TextBox ID="txlinkman" runat="server"></asp:TextBox>
	           
	        </td>
	        <td align=left >输入您要查询的用户名</td>
	        <td  align=left>
	            <asp:TextBox ID=txlogin runat=server></asp:TextBox>
	        
	        <td align=left>
                <asp:Button ID="Button1" runat="server" Text="查询" OnClick="Button1_Click" />
                <asp:Button ID="Button2" runat="server" Text="新增" OnClick="Button2_Click" Visible="false"/>
            </td>
	    </tr>


	    <tr>
	        <td align=left>输入要查询的手机号</td>
	        <td align=left>
                <asp:TextBox ID="txtPhone" runat="server"></asp:TextBox>
            </td>
	        <td align=left>
                <asp:Button ID="bntChaXun" runat="server" Text="查询" onclick="bntChaXun_Click" />
	        </td>
	        <td></td>
	        <td align=left>
                &nbsp;</td>
	    </tr>
	    <tr>
	        <td colspan=5 align=center>
	        <asp:datagrid id="dgExamProj" PageSize="20" GridLines="Horizontal" BackColor="White" BorderColor="Black"
							CellPadding="3" Font-Name="Verdana" Font-Size="8pt" HeaderStyle-BackColor="#cecfd6" AutoGenerateColumns="False"
							AllowSorting="True" Font-Names="Verdana" AllowPaging="True" Runat="server" Width="100%" OnItemDataBound="dgExamProj_ItemDataBound" OnItemCommand="dgExamProj_ItemCommand">
							<SelectedItemStyle BorderColor="#FFC080" BackColor="#FFC080"/>
							<AlternatingItemStyle BackColor="OldLace"></AlternatingItemStyle>
							<ItemStyle HorizontalAlign="center" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False"></ItemStyle>							<HeaderStyle HorizontalAlign="Center" Width="50%" BackColor="#EFF0C1" Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False"></HeaderStyle>
							<Columns>
							
							<asp:TemplateColumn HeaderText="用户名">
									<ItemTemplate>
									<asp:Label id="lblPack" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.UserID") %>' Visible="False"></asp:Label>
									<asp:Label id="lblTestItems" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.UserName") %>' ></asp:Label>
									</ItemTemplate>
								</asp:TemplateColumn>
										
					<asp:TemplateColumn HeaderText="姓名" >
						<ItemTemplate>
						<asp:Label id="lblId" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.UserID") %>' Visible="False"></asp:Label>
                             <%# DataBinder.Eval(Container, "DataItem.UserName")%>  
                       <%-- <asp:Label id="lblPname" runat="server" Text='<%# Eval(Username) %>' ></asp:Label>--%>
						</ItemTemplate>
                             <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False" Font-Underline="False" HorizontalAlign="Center" />
				    </asp:TemplateColumn>
								
				    <asp:TemplateColumn HeaderText="联系方式">
						<ItemTemplate>
						<asp:Label id="lblPhone" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.PhoneNum") %>' ></asp:Label>
						</ItemTemplate>
					</asp:TemplateColumn>
					
					<asp:TemplateColumn HeaderText="积分">
						<ItemTemplate>
						<asp:Label id="lblIntegral" runat="server" Text='<%# DataBinder.Eval(Container, "DataItem.TotalMoney") %>' ></asp:Label>
						</ItemTemplate>
					</asp:TemplateColumn>
	<%-----------------------------------------------------------%>
				<asp:TemplateColumn HeaderText="积分管理">
                                    <ItemTemplate>
                                          <asp:LinkButton ID="lbtnJF" runat="server" CommandName="InsertJF" CommandArgument='<%# DataBinder.Eval(Container, "DataItem.UserID") %>' >添加</asp:LinkButton>
                                    </ItemTemplate>
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                    <HeaderStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                </asp:TemplateColumn>
       <%-----------------------------------------------------------%>                         	
					
								
                                <asp:TemplateColumn HeaderText="修改">
                                    <ItemTemplate>
                                          <a href="UserUpdate.aspx?UserID=<%# Eval("UserID") %>">修改</a>
                                    </ItemTemplate>
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                    <HeaderStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                </asp:TemplateColumn>
                                <asp:TemplateColumn HeaderText="删除">
                                    <ItemStyle Font-Bold="False" Font-Italic="False" Font-Overline="False" Font-Strikeout="False"
                                        Font-Underline="False" HorizontalAlign="Center" />
                                    <ItemTemplate>
                                        <asp:LinkButton ID="LinkButton2" runat="server" CommandName="delete"  
            OnClientClick="javascript:return confirm('确认删除?');" >删除</asp:LinkButton>
                                    </ItemTemplate>
                                </asp:TemplateColumn>
							
								
							</Columns>
							<PagerStyle  Visible="False"></PagerStyle>
						</asp:datagrid>
                   
            </td>
	    </tr>
	     <tr><td width="100%" colspan="5"> 
             <cc1:Pager ID="Pager1" runat="server" GenerateFirstLastSection="True" 
      GenerateGoToSection="True" GenerateHiddenHyperlinks="False" 
      QueryStringParameterName="CurrentPage" OnCommand="pager_Command" 
      GoToStyle="text" OfClause="/" PageClause="页" PageSize="15" />
             </td></tr>
   
	</table>
	
	</div>
    
    </form>
    
        <script language="javascript" type="text/javascript">
            function SeleAct(obj) {
                if (obj == "remove") {
                    document.getElementById("CategoryTitle").className = 'show';
                    document.getElementById("Button1").className = 'show';
                }
                else {
                    document.getElementById("CategoryTitle").className = 'hidden';
                    document.getElementById("Button1").className = 'hidden';
                }
            }
     </script>
</body>
</html>
