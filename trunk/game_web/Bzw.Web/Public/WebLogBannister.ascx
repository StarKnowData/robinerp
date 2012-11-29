<%@ Control Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Public.Public_WebLogBannister"%>
 <div  id="record" class="rank_manu"> 
	<a id="g1" href="/Manage/Pay/PointCardLog.aspx" >点卡充值记录</a>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g2" href="/Manage/Pay/PayMoneyLog.aspx" >网银充值记录</a>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g3" href="/Manage/BankMoneyOperaLog.aspx" >存取记录</a>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g4" href="/Manage/BankTransLog.aspx?type=1" >转账记录</a>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g5" href="/Manage/BuyPropLog.aspx" >购买道具记录</a>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g6" href="/Manage/BuyVipLog.aspx" >购买VIP记录</a>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g7" href="/Manage/PrizeLog.aspx" >奖品兑换记录</a>
	|&nbsp;&nbsp;<a id="g8" href="/Manage/GetVipLog.aspx" >获赠VIP记录</a>
	<br />|&nbsp;&nbsp;<a id="g9" href="/Manage/FasciExchangeLog.aspx" >魅力值兑换记录</a>
	 
</div>

<script type="text/javascript">
<!--
    function SetLogNav(n){
        var ulnav = document.getElementById('record');
        var els = ulnav.getElementsByTagName('a');
        for(var i=0;i<els.length;i++){
            //alert(els[i].id);
            els[i].className='';
        }
        
        document.getElementById('g'+n).className='rank_manubg';
    }
//-->
</script>
