<%@ Control Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Public.Public_RankLeft" %>
<div id="phb_left">
    <h3>
        <img src="/Images/left_tit02.jpg" alt="" /></h3>
    <ul class="php_ul">
        <li class="php_d"><a href="/ContestRank.aspx" class="link02">淘汰赛排行</a></li>
        <li class="php_d"><a href="/RankMoney.aspx" class="link02">财富排行</a></li>
        <li class="php_d"><a href="/RankFascination.aspx" class="link02">魅力排行</a></li>
        <li class="php_d"><a href="/RankOnLineTime.aspx" class="link02">在线时间排行</a></li>
        <li class="php_d"><a href="/RankGameTime.aspx" class="link02">游戏时间排行</a></li>
        <li class="php_d">
            <p>
                <a href="javascript:display(2)" title="混战场排行" class="link02">混战场排行</a></p>
            <div class="php_s">
                <ul>
                    <ol id="battle">
                        <asp:Repeater ID="Repeater1" runat="server">
                            <ItemTemplate>
                                <li><a href="/BattleRank.aspx?id=<%#Eval("GameNameID") %>&name=<%#Server.UrlEncode(Eval("GameName").ToString()) %>">
                                    <%#Eval( "GameName" )%>
                                </a></li>
                            </ItemTemplate>
                        </asp:Repeater>
                    </ol>
                </ul>
            </div>
        </li>
        <li class="php_d"><a href="javascript:display(1)" class="link02">游戏积分排行</a>
            <div class="php_s">
                <ul>
                    <ol id="point">
                        <asp:Repeater ID="rpList" runat="server">
                            <ItemTemplate>
                                <li><a href="/Ranking.aspx?id=<%#Eval("NameID") %>&name=<%#Server.UrlEncode(Eval("ComName").ToString()) %>"
                                    title="<%#Eval("ComName") %>">
                                    <%#Eval("ComName") %>
                                </a></li>
                            </ItemTemplate>
                        </asp:Repeater>
                    </ol>
                </ul>
            </div>
        </li>
    </ul>
</div>

<script type="text/javascript">
    function display(sign) {
        var pointDis = document.getElementById("point").style.display;
        var battleDis = document.getElementById("battle").style.display;
        if (sign == 1) {
            if (pointDis == "none")
                document.getElementById("point").style.display = "block";
            else
                document.getElementById("point").style.display = "none";
        }
        else {

            if (battleDis == "none")
                document.getElementById("battle").style.display = "block";
            else
                document.getElementById("battle").style.display = "none";

        }

    }
</script>

