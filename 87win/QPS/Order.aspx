<%@ Page Title="" Language="C#" MasterPageFile="~/MainMaser.Master" EnableEventValidation="false"  AutoEventWireup="true" CodeBehind="Order.aspx.cs" Inherits="QPS.Web.Order" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    
     <!--nymiddle[[-->
     <div class="mid">
           <div class="titlec">
            <span><a href="#">武昌区</a>><a href="#">棋牌室</a>><a href="#">预订</a></span>
           </div>
          <div class="ydsx">
              <h2><a href="#">免费在线预订</a></h2><h3><a href="#">填写预订信息</a></h3><h4><a href="#">预订成功</a></h4>
           </div>
     <div class="titlec">
          <span>预订信息</span>
     </div>
     <div  class="xxb">
         <asp:DataList ID="DataList1" runat="server" width="960px">
         <ItemTemplate>
          <table width="100%" border="0" cellpadding="5" cellspacing="1" bgcolor="#E6E6E6">
       <tr>
         <td align="center" bgcolor="#F2F2F2"><span class="STYLE1">棋牌室名称</span></td>
         <td align="center" bgcolor="#F2F2F2"><span class="STYLE1">棋牌室类型</span></td>
         <td align="center" bgcolor="#F2F2F2"><span class="STYLE1">棋牌室价格</span></td>
         <td align="center" bgcolor="#F2F2F2"><span class="STYLE1">棋牌室地区</span></td>
       </tr>
       <tr>
         <td align="center" bgcolor="#FFFFFF" class="STYLE6"><%# Eval("Name").ToString()%></td>
         <td align="center" bgcolor="#FFFFFF" class="STYLE5"><%# Eval("RoomType").ToString()%></td>
         <td align="center" bgcolor="#FFFFFF" class="STYLE5"><span class="STYLE7"><%# Eval("RoomPrice").ToString()%></span>元</td>
         <td align="center" bgcolor="#FFFFFF" class="STYLE5"><%# Eval("Are").ToString()%></td>
       </tr>
       <tr>
         <td colspan="4" align="left" bgcolor="#FFFFFF"><span class="STYLE2">地址：<%# Eval("Address").ToString()%></span></td>
         </tr>
     </table>
         </ItemTemplate>
         </asp:DataList>
         </div>
     <div class="titlec">
          <span>预订人信息（必填）</span>
     </div>
     <div class="ydrxx">
          <span>预订人信息</span>
          <ul>
              <li><h3>预订人信息：</h3> 
                <asp:TextBox ID="txbOrderPersonInfo" runat="server" CssClass="xxa1"></asp:TextBox> 
              </li>
              <li><h3>手机号码：</h3>   <asp:TextBox ID="txbPhone" runat="server" CssClass="xxa1"></asp:TextBox> <h6>为保证准备通知到您，若未填写手机号码请正确填写手机号码。</h6>
</li>
          </ul>
     </div>
     <div class="ydrxx">
          <span>预订信息</span>
          <ul>
              <li class="rili"><h3>预定时间：</h3> 
                  <asp:Calendar ID="Calendar1" runat="server" cssClass="xxa4" ForeColor="Black" 
                      BackColor="White" BorderColor="#999999" CellPadding="4" 
                      DayNameFormat="Shortest" Font-Names="Verdana" Font-Size="8pt" Height="180px" 
                      Width="200px">
                      <SelectedDayStyle BackColor="#666666" Font-Bold="True" ForeColor="White" />
                      <SelectorStyle BackColor="#CCCCCC" />
                      <WeekendDayStyle BackColor="#FFFFCC" />
                      <TodayDayStyle BackColor="#CCCCCC" ForeColor="Black" />
                      <OtherMonthDayStyle ForeColor="#808080" />
                      <NextPrevStyle VerticalAlign="Bottom" />
                      <DayHeaderStyle BackColor="#CCCCCC" Font-Bold="True" Font-Size="7pt" />
                      <TitleStyle BackColor="#999999" BorderColor="Black" Font-Bold="True" />
                  </asp:Calendar>
                <asp:DropDownList ID="dplStartTime" runat="server" cssClass="xxa4"> 
                  <asp:ListItem Value="0">0点</asp:ListItem>
                    <asp:ListItem Value="1">1点</asp:ListItem>
                     <asp:ListItem Value="2">2点</asp:ListItem>
                      <asp:ListItem Value="3">3点</asp:ListItem>
                       <asp:ListItem Value="4">4点</asp:ListItem>
                        <asp:ListItem Value="5">5点</asp:ListItem>
                         <asp:ListItem Value="6">6点</asp:ListItem> 
                         <asp:ListItem Value="7">7点</asp:ListItem>
                          <asp:ListItem Value="8">8点</asp:ListItem>
                           <asp:ListItem Value="9">9点</asp:ListItem>
                            <asp:ListItem Value="10">10点</asp:ListItem>
                             <asp:ListItem Value="11">11点</asp:ListItem>
                              <asp:ListItem Value="12">12点</asp:ListItem>
                               <asp:ListItem Value="13">13点</asp:ListItem>
                                <asp:ListItem Value="14">14点</asp:ListItem>
                                 <asp:ListItem Value="15">15点</asp:ListItem>
                                  <asp:ListItem Value="16">16点</asp:ListItem>
                                  <asp:ListItem Value="17">17点</asp:ListItem>
                                  <asp:ListItem Value="18">18点</asp:ListItem>
                                  <asp:ListItem Value="19">19点</asp:ListItem>
                                  <asp:ListItem Value="20">20点</asp:ListItem>
                                  <asp:ListItem Value="21">21点</asp:ListItem>
                                  <asp:ListItem Value="22">22点</asp:ListItem>
                                  <asp:ListItem Value="23">23点</asp:ListItem>
                 </asp:DropDownList>
              <h4>到</h4>
                    <asp:Calendar ID="Calendar2" runat="server" cssClass="xxa4" ForeColor="Black" 
                      BackColor="White" BorderColor="#999999" CellPadding="4" 
                      DayNameFormat="Shortest" Font-Names="Verdana" Font-Size="8pt" Height="180px" 
                      Width="200px">
                        <SelectedDayStyle BackColor="#666666" Font-Bold="True" ForeColor="White" />
                        <SelectorStyle BackColor="#CCCCCC" />
                        <WeekendDayStyle BackColor="#FFFFCC" />
                        <TodayDayStyle BackColor="#CCCCCC" ForeColor="Black" />
                        <OtherMonthDayStyle ForeColor="#808080" />
                        <NextPrevStyle VerticalAlign="Bottom" />
                        <DayHeaderStyle BackColor="#CCCCCC" Font-Bold="True" Font-Size="7pt" />
                        <TitleStyle BackColor="#999999" BorderColor="Black" Font-Bold="True" />
                  </asp:Calendar>
                  <asp:DropDownList ID="dplEndTime" runat="server" cssClass="xxa4"> 
                             <asp:ListItem Value="0">0点</asp:ListItem>
                    <asp:ListItem Value="1">1点</asp:ListItem>
                     <asp:ListItem Value="2">2点</asp:ListItem>
                      <asp:ListItem Value="3">3点</asp:ListItem>
                       <asp:ListItem Value="4">4点</asp:ListItem>
                        <asp:ListItem Value="5">5点</asp:ListItem>
                         <asp:ListItem Value="6">6点</asp:ListItem> 
                         <asp:ListItem Value="7">7点</asp:ListItem>
                          <asp:ListItem Value="8">8点</asp:ListItem>
                           <asp:ListItem Value="9">9点</asp:ListItem>
                            <asp:ListItem Value="10">10点</asp:ListItem>
                             <asp:ListItem Value="11">11点</asp:ListItem>
                              <asp:ListItem Value="12">12点</asp:ListItem>
                               <asp:ListItem Value="13">13点</asp:ListItem>
                                <asp:ListItem Value="14">14点</asp:ListItem>
                                 <asp:ListItem Value="15">15点</asp:ListItem>
                                  <asp:ListItem Value="16">16点</asp:ListItem>
                                  <asp:ListItem Value="17">17点</asp:ListItem>
                                  <asp:ListItem Value="18">18点</asp:ListItem>
                                  <asp:ListItem Value="19">19点</asp:ListItem>
                                  <asp:ListItem Value="20">20点</asp:ListItem>
                                  <asp:ListItem Value="21">21点</asp:ListItem>
                                  <asp:ListItem Value="22">22点</asp:ListItem>
                                  <asp:ListItem Value="23">23点</asp:ListItem>
                   </asp:DropDownList>
              </li>
              <li><h3>人数：</h3> <asp:TextBox ID="txbNum" runat="server" CssClass="xxa3"></asp:TextBox> </li>
          </ul>
     </div>
     <div class="ydrxx">
          <span>其他（选填）如您有特殊要求，请再这里注明</span>
          <ul>
              <li><h3>其它要求：</h3> <textarea name="textfield3" id="textfield3" class="xxa5"></textarea></li>
              <li>
                  <asp:Button ID="btnSub" runat="server" Text="" CssClass="xxa6" onclick="btnSub_Click" /></li>
          </ul>
     </div>
     </div>
     <!--nymiddle]]-->
</asp:Content>
