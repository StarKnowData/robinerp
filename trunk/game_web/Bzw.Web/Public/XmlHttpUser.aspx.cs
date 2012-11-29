using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

using Utility;
using Bzw.Data;
using System.Xml;
using System.IO;
using System.Web.UI.MobileControls;
using BLL;
using System.Collections.Generic;
using BCST.Common;
using UiCommon;

public partial class Public_XmlHttpUser : UiCommon.BasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        try
        {
            string stype = Common.GetStringOfUrl("type");
            switch (stype)
            {
                //1.判断用户是否登录
                case "islogin":
                    if (UiCommon.UserLoginInfo.IsLogin)
                    {
                        Response.Write("1");//表示已登录
                    }
                    else
                    {
                        Response.Write("0");//表示未登录
                    }
                    break;
                //2.判断用户名是否存在
                case "nameexist":
                    ExistName();
                    break;
                //3.注册时，判断用户名是否存在，是否包含敏感关键字，如"admin"
                case "regnameexist":
                    ExistNameOfReg();
                    break;
                //4.用户昵称是否存在
                case "nickexist":
                    ExistNick();
                    break;
                //5.Email是否存在
                case "emailexist":
                    ExistEmail();
                    break;
                //6.验证码比较
                case "validcode":
                    string vcode = Common.GetStringOfUrl("code");
                    if (UiCommon.ValidCode.CurrentCode == null)
                    {
                        Response.Write("-1");//验证码失效
                    }
                    else if (UiCommon.ValidCode.CurrentCode != vcode)
                    {
                        Response.Write("1");//验证码输入错误
                    }
                    else
                    {
                        Response.Write("0");//验证码输入正确
                    }
                    break;
                //7.道具购买
                case "buydaoju":
                    BuyDaoJu();
                    break;
                //8.道具赠送
                case "zsdaoju":
                    DaoJuZS();
                    break;
                //9.用户修改昵称时，判断是否已存在
                case "upnickexist":
                    ExistNickOfUpdate();
                    break;
                //10.被推广人达到有效推广后，进行结算处理的方法
                case "tgbalance":
                    TuiguangBalance();
                    break;
                //11.获取当前登录用户的银行金额
                case "lgusermoney":
                    Response.Write(UiCommon.StringConfig.AddZeros(new BLL.Member().GetBankMoney(UiCommon.UserLoginInfo.UserID)));
                    break;
                case "tgnameexist":
                    ExistTGName();
                    break;
                //12.判断玩家金币是否可以抽取奖品
                case "lotterystart": LotteryS();
                    //   Response.Write("3");
                    HttpContext.Current.ApplicationInstance.CompleteRequest();

                    break;
                case "lotterydo": Response.Write(Lottery1()); HttpContext.Current.ApplicationInstance.CompleteRequest(); break;
                //15.判断身份证号是否还能再注册
                case "cardnovalid": CardNoRegCount(); break;
                //16.报名
                case "matchapply": MatchApply(); break;
                //17.退赛
                case "matchexit": ExitMatch(); break;
                default:

                    break;
            }
        }
        catch (Exception ex)
        {

            Response.Write(ex.Message + ex.Source + ex.StackTrace);
        }
    }

    public void ExistTGName()
    {
        string username = Common.FilterString(Common.GetStringOfUrl("username"));
        if (new BLL.Promotion().ExistTGUser(username))
        {
            Response.Write("1");
        }
        else
        {
            Response.Write("0");
        }
    }

    public void ExistName()
    {
        string username = Common.FilterString(Common.GetStringOfUrl("username"));
        if (new BLL.Member().ExistName(username))
        {
            Response.Write("1");
        }
        else
        {
            Response.Write("0");
        }
    }

    public void ExistNameOfReg()
    {
        string username = Common.FilterString(Common.GetStringOfUrl("username"));
        if (BLL.Config.ExistBanWord(username, BLL.Config.BadWordOfUserName()) || new BLL.Member().ExistName(username))
        {
            Response.Write("1");
        }
        else
        {
            Response.Write("0");
        }
    }

    public void ExistNick()
    {
        string username = Common.FilterString(Common.GetStringOfUrl("nickname"));
        if (BLL.Config.ExistBanWord(username, BLL.Config.BadWordOfNickName()) || new BLL.Member().ExistNick(username))
        {
            Response.Write("1");
        }
        else
        {
            Response.Write("0");
        }
    }

    public void ExistEmail()
    {
        string username = Common.FilterString(Common.GetStringOfUrl("email"));
        if (new BLL.Member().ExistEmail(username))
        {
            Response.Write("1");
        }
        else
        {
            Response.Write("0");
        }
    }

    public void ExistNickOfUpdate()
    {
        string nickname = Common.FilterString(Common.GetStringOfUrl("nickname"));
        string userid = UiCommon.UserLoginInfo.UserID.ToString();
        if (BLL.Config.ExistBanWord(nickname, BLL.Config.BadWordOfNickName()) || new BLL.Member().ExistNick(userid, nickname))
        {
            Response.Write("1");
        }
        else
        {
            Response.Write("0");
        }
    }

    public void BuyDaoJu()
    {
        string userId = UiCommon.UserLoginInfo.UserID;
        string propId = Common.SqlEncode(Common.GetStringOfUrl("id"));

        DataRow drDaoju = new BLL.DaoJu().GetInfo(propId);
        if (drDaoju != null)
        {
            int count = Common.GetIntOfUrl("count");

            int price = Convert.ToInt32(drDaoju["Price"]);// Common.GetIntOfUrl("price");
            int vipPrice = Convert.ToInt32(drDaoju["VipPrice"]);

            //1.读取当前登录用户的信息，UserID,BankMoney,VipTime
            DataRow dr = new BLL.Member().GetInfoInTUserInfo(userId);
            string vipTime = "1970-01-01 08:00:00";
            Int64 bankMoney = 0;
            if (dr != null)
            {
                //购买vip的公式：当前日期+购买天数*60*60*24
                vipTime = dr["VipTime2"].ToString();
                bankMoney = Convert.ToInt64(dr["BankMoney"]);
            }

            //2.判断是否有足够的金币购买该道具
            int buyMoney = 0;
            if (DateTime.Now < Convert.ToDateTime(vipTime))
            {
                buyMoney = vipPrice * count;
            }
            else
            {
                buyMoney = price * count;
            }

            if (buyMoney < 0)//数据溢出
            {
                Response.Write("buysb");
                return;
            }

            if (bankMoney < buyMoney)
            {
                Response.Write("notmoney");
            }
            else
            {
                //3.金币足够，判断三种类型的道具：普通道具、1小时双倍积分卡、3小时双倍积分卡
                int doublePointTime = 0;
                if (propId.Trim() == "6")
                {
                    //1小时双倍积分卡
                    doublePointTime = count * 60 * 60;
                }
                else if (propId.Trim() == "7")
                {
                    //3小时双倍积分卡
                    doublePointTime = count * 60 * 60 * 3;
                }

                //4.提交数据
                int iRows = new BLL.Member().BuyDaoJu(userId, propId, count, buyMoney, doublePointTime);
                if (iRows > 0)
                {
                    Response.Write("buycg");
                }
                else
                {
                    Response.Write("buysb");
                }
            }
        }
        else
        {
            Response.Write("nodaoju");
        }
    }

    public void DaoJuZS()
    {
        string userId = UiCommon.UserLoginInfo.UserID;
        string userName = UiCommon.UserLoginInfo.UserName;
        string propId = Common.SqlEncode(Common.GetStringOfUrl("id"));
        string targetName = Common.GetStringOfUrl("targetname");
        int count = Common.GetIntOfUrl("count");

        BLL.Member member = new BLL.Member();
        if (userName.Trim() == targetName.Trim())
        {
            //1.如果被赠送用户是自己，不允许赠送
            Response.Write("myself");
        }
        else if (!member.ExistName(Common.SqlEncode(targetName)))
        {
            //2.被赠送的用户不存在
            Response.Write("nouser");
        }
        else if (count > member.GetDaoJuCount(userId, propId))
        {
            //3.赠送人道具库中的道具数量不足或没有
            Response.Write("nodaoju");
        }
        else
        {
            //4.赠送
            int iRows = member.ZengsongDaoJu(userId, member.GetUserID(targetName), propId, count);
            if (iRows > 0)
            {
                Response.Write("zsdjcg");
            }
            else
            {
                Response.Write("zsdjsb");
            }
        }
    }

    public void TuiguangBalance()
    {
        string tgUserId = Common.SqlEncode(Common.GetStringOfUrl("tguserid"));
        string userId = Common.SqlEncode(Common.GetStringOfUrl("userid"));
        //返回值：-1未达到有效推广 ， 0达到有效推广 ， 或其它值
        int iRe = new BLL.Member().TuiguangBalance(tgUserId, userId);
        Response.Write(iRe);
    }
    //判断玩家金币是否能够抽奖
    public void LotteryS()
    {
        string userid = UiCommon.UserLoginInfo.UserID;

        Int64 gMoney = 0;
        Int64 sMoney = 0;
        Int64 jMoney = 0;
        Int64 userMoney = 0;
        DataTable dt = DbSession.Default.FromSql("select * from Web_LotterConfig").ToDataTable();
        if (dt.Rows.Count > 0)
        {
            gMoney = Convert.ToInt64(dt.Rows[0]["GoldMoney"]);
            sMoney = Convert.ToInt64(dt.Rows[0]["SilverMoney"]);
            jMoney = Convert.ToInt64(dt.Rows[0]["JadeMoney"]);
        }
        userMoney = Convert.ToInt64(new BLL.Member().GetBankMoney(userid));

        string str;
        if (userMoney >= gMoney)
            str = "3";
        else
        {
            if (userMoney >= jMoney)
                str = "2";
            else
            {
                if (userMoney >= sMoney)
                    str = "1";
                else
                    str = "0";
            }
        }
        XmlDocument xml = new XmlDocument();
        string xmlPath = Server.MapPath("/Upload/xml/LotterConfig.xml");
        string needMoney = "";
        if (!File.Exists(xmlPath))
        {

        }
        else
        {
            xml.Load(xmlPath);
            string xp = "//item[@id='1']";

            XmlElement xmlRoot = xml.DocumentElement;//取得文档的根节点
            XmlNode xn = xmlRoot.SelectSingleNode(xp);
            needMoney = needMoney + xn["Gold"].InnerText;
            needMoney = needMoney + "," + xn["Jade"].InnerText;
            needMoney = needMoney + "," + xn["Silver"].InnerText;
        }

        Response.Write(str + (needMoney == "" ? "" : "," + needMoney));
        HttpContext.Current.ApplicationInstance.CompleteRequest();
        // Response.Redirect("/Manage/Lottery.aspx", false);
    }
    //开始抽奖
    public string Lottery1()
    {

        string type = Common.FilterString(Common.GetStringOfUrl("method"));
        Lottery lo = new Lottery();
        //判断玩家是否被指定中奖
        int speAwardid = lo.GetAwardSpecial(UiCommon.UserLoginInfo.UserID);
        //   int speAwardid = lo.GetAwardSpecial("207");
        int result = 0;

        if (speAwardid != 0)
        {
            //玩家指定中奖
            result = lo.AddAwardLog(UiCommon.UserLoginInfo.UserID, speAwardid.ToString(), type, "0");
            // lo.AddAwardLog("207", speAwardid.ToString(), type);

        }
        else
        {
            //抽取随机奖品id
            int awradid = Convert.ToInt32(GetAwardId(type));

            //获得奖品
            //if (awradid > 0)
            //{
            //抽中奖品

            result = lo.AddAwardLog(UiCommon.UserLoginInfo.UserID, awradid.ToString(), type, "1");

            if (result == -2 || result == 1)
                speAwardid = 0;
            if (result == 0)
                speAwardid = awradid;

        }

        //返回奖品的排序号
        return GetAwardOrder(speAwardid);
    }
    //获得中奖的id
    public string GetAwardId(string type)
    {

        XmlDocument xml = new XmlDocument();
        string xmlPath = Server.MapPath("/Upload/xml/Lotter.xml");
        if (!File.Exists(xmlPath))
        {
            return "";
        }
        xml.Load(xmlPath);

        string strRateType = string.Empty;
        if (type == "0")
            strRateType = "GoldRate";
        if (type == "1")
            strRateType = "JadeRate";
        if (type == "2")
            strRateType = "SilverRate";
        List<Lottery> list = new List<Lottery>();
        int num = 0;
        int j = 1;

        XmlNodeList topM = xml.DocumentElement.ChildNodes;
        string str = "";
        foreach (XmlElement element in topM)
        {
            Lottery lo = new Lottery();
            lo.ID = Convert.ToInt32(element.Attributes["id"].Value);
            int m = 0;
            foreach (XmlElement xn in element.ChildNodes)
            {

                if (xn.Name == strRateType && xn.InnerText != "0")
                {
                    lo.Min = num + 1;
                    num += Convert.ToInt32(xn.InnerText) * 100;
                    str += ":" + num;
                    m = 1;
                }
                else
                {

                }

            }
            lo.Max = num;
            lo.OrderID = j;
            j++;
            if (m == 1)
            {

                list.Add(lo);
            }


        }

        Random ran = new Random();
        int i = ran.Next(1, 10001);
        //如果第一次随机没有选中，则在可中选项中随机选取一个

        foreach (Lottery lo1 in list)
        {
            str += ":" + lo1.Max;
            if (lo1.Min != lo1.Max)
            {
                if (i >= lo1.Min && i <= lo1.Max)
                {
                    return lo1.ID.ToString(); ;
                }
                else
                {
                    
                }
            }

        }

        return "0";
    }
    //返回Flash中奖奖品的序列号
    public string GetAwardOrder(int awardid)
    {

        XmlDocument xml = new XmlDocument();
        string xmlPath = Server.MapPath("/Upload/xml/Lotter.xml");
        if (!File.Exists(xmlPath))
        {
            return "";
        }
        xml.Load(xmlPath);

        List<Lottery> list = new List<Lottery>();

        int j = 1;
        int orderid = 0;
        XmlNodeList topM = xml.DocumentElement.ChildNodes;
        foreach (XmlElement element in topM)
        {
            Lottery lo = new Lottery();
            // lo.ID = Convert.ToInt32(element.Attributes["id"].Value);

            lo.ID = Convert.ToInt32(element.Attributes["id"].Value);
            lo.OrderID = j;
            j++;
            if (lo.ID == awardid)
            {
                orderid = lo.OrderID;
            }
            if (lo.Min != lo.Max)
            {
                list.Add(lo);
            }
        }

        if (orderid == 0)
        {

            return "12";

        }
        else
            return orderid.ToString();

    }
    //身份证注册次数限制
    private void CardNoRegCount()
    {
        string CardNo = Common.FilterString(Common.GetStringOfUrl("cardno"));
        if (new BLL.Member().UserRegCardNoValid(CardNo) == -1)
        {
            Response.Write("0");//不能
        }
        else
        {
            Response.Write("1");//能
        }
    }
    private void MatchApply()
    {
        string contestId = Common.FilterString(Common.GetStringOfUrl("id"));

        try
        {
            string uid = Common.FilterString(Common.GetIntOfUrl("uid").ToString());
            if (!UiCommon.UserLoginInfo.IsLogin)
            {
                //判断是否从平台跳转过来的

                string token = Common.FilterString(Common.GetStringOfUrl("token2").ToString());

                if (CommonManager.String.IsInteger(uid) && token.Trim().Length > 0)
                {
                    string un = new BLL.Member().GetNameByUserID(uid, token);
                    if (!string.IsNullOrEmpty(un))
                    {
                        UserLoginInfo.SetInfo(uid, un);

                    }
                    else
                    {
                        Response.Write("抱歉，报名失败，可能是服务器繁忙，请稍后再试！");
                        return;
                    }
                }
            }
            Dictionary<string, object> dic = new Dictionary<string, object>();
            DbSession.Default.FromProc("Web_pApplyMatch").AddInputParameter("@UserID", DbType.Int32, UserLoginInfo.UserID)
                .AddInputParameter("@ContestID", DbType.Int32, Request.QueryString["id"].ToString())
                .AddReturnValueParameter("@ReturnValue", DbType.Int32)
               .Execute(out dic);
            if (dic.Count <= 0)
            {
                Response.Write("抱歉，报名失败，可能是服务器繁忙，请稍后再试！");

                return;
            }

            if (dic["ReturnValue"].ToString() == "-1")
            {
                Response.Write("抱歉，报名失败，您银行的" + ConfigurationManager.AppSettings["moneyName"].ToString() + "不足！");

                return;
            }
            if (dic["ReturnValue"].ToString() == "-2")
            {
                Response.Write("已成功报名！");
                return;

            }
            Response.Write("报名成功！");
        }
        catch (Exception ex)
        {
            Response.Write("报名失败，服务器未知错误！");
        }
    }
    private void ExitMatch()
    {
        try
        {
            string contestId = Common.FilterString(Common.GetStringOfUrl("id"));
            string hids = Common.FilterString(Common.GetStringOfUrl("hidTime"));
            string uid = Common.FilterString(Common.GetIntOfUrl("uid").ToString());
            if (!UiCommon.UserLoginInfo.IsLogin)
            {
                //判断是否从平台跳转过来的

                string token = Common.FilterString(Common.GetStringOfUrl("token2").ToString());
                if (CommonManager.String.IsInteger(uid) && token.Trim().Length > 0)
                {
                    string un = new BLL.Member().GetNameByUserID(uid, token);
                    if (!string.IsNullOrEmpty(un))
                    {
                        UserLoginInfo.SetInfo(uid, un);

                    }
                    else
                    {
                        Response.Write("抱歉，退赛失败，可能是服务器繁忙，请稍后再试！");
                        return;
                    }
                }
            }
            DateTime dt1 = Convert.ToDateTime(hids);
            if (DateTime.Compare(dt1, DateTime.Now) < 0)
            {
                Response.Write("抱歉，比赛已开始，不能退赛！");
                return;

            }
            DbSession.Default.FromProc("Web_pExitMatch")
                .AddInputParameter("@UserID", DbType.Int32, UiCommon.UserLoginInfo.UserID)
                .AddInputParameter("@ContestID", DbType.Int32, contestId)
                .Execute();
            Response.Write("退赛成功！");
        }
        catch (Exception ex)
        {
            Response.Write("退赛失败，服务器未知错误！");
        }
    }
}
