using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using Bzw.Data;
using System.Web.UI;
using BCST.Common;
using System.Configuration;

namespace Bzw.Inhersits.Manage
{
    public partial class Manage_MatchApply : UiCommon.ManageBasePage
    {
        /// <summary>
        /// Head1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

        /// <summary>
        /// webmeta1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected UserControl webmeta1;

        /// <summary>
        /// webTopOne 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected UserControl webtop1;

        /// <summary>
        /// webshortcutkey1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        //      protected global::System.Web.Public.WebShortCutKey webshortcutkey1;

        /// <summary>
        /// webservice1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected UserControl webservice1;

        /// <summary>
        /// webFooterone 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected UserControl webFooterone;

        protected global::System.Web.UI.WebControls.HiddenField hids;
        protected global::System.Web.UI.WebControls.HiddenField hide;

        protected global::System.Web.UI.WebControls.Panel panShow;
        /// <summary>
        /// imageField2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputSubmit imageField2;

        protected global::System.Web.UI.HtmlControls.HtmlInputButton btnExit;
        protected global::System.Web.UI.HtmlControls.HtmlForm Form1;
        protected global::System.Web.UI.WebControls.Repeater rptAward;
        public string MatchID;
        public string MatchName;
        public string MatchSend;
        public string StartTime;
        public string EndTime;
        public string NeedMoney;
        public string MatchContent;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                if (Request.QueryString["id"] == null || !Utility.Common.IsNumber(Request.QueryString["id"]))
                {
                    Response.Redirect("/MatchList.aspx");
                }
                DataTable dt = DbSession.Default.FromSql("select top 1 * from Web_VTContestRoom where startTime>@NowDate and contestid=@ContestID order by StartTime")
                    .AddInputParameter("@NowDate", DbType.DateTime, DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"))
                    .AddInputParameter("@ContestID", DbType.Int32, Request.QueryString["id"])
                    .ToDataTable();
                if (dt.Rows.Count > 0)
                {
                    MatchID = dt.Rows[0]["ContestID"].ToString();
                    MatchName = dt.Rows[0]["ComName"].ToString();
                    StartTime = dt.Rows[0]["StartTime"].ToString();
                    EndTime = dt.Rows[0]["EndTime"].ToString();
                    MatchSend = dt.Rows[0]["AwardContent"].ToString();
                    NeedMoney = dt.Rows[0]["EntryFee"].ToString();
                    MatchContent = dt.Rows[0]["MatchContent"].ToString();
                    hids.Value = StartTime;
                    hide.Value = MatchID;
                    int count = (int)DbSession.Default.FromSql("select count(1) from TContestUserRecord where userid=" + UiCommon.UserLoginInfo.UserID + " and contestid=" + MatchID + " and ContestCount=0").ToScalar();
                    if (count != 0)
                    {
                        imageField2.Disabled = true;
                        imageField2.Value = "已报名";
                        btnExit.Visible = true;
                    }
                    int sendTypeID = Convert.ToInt32(dt.Rows[0]["SendTypeID"].ToString());
                    DataTable dt2 = DbSession.Default.FromSql("select top 10 * from Web_MatchAwardConfig where TypeID=@TypeID order by Rank").AddInputParameter("@TypeID", DbType.Int32, sendTypeID).ToDataTable();
                    if (dt2.Rows.Count > 0)
                    {
                        rptAward.DataSource = dt2;
                        rptAward.DataBind();
                    }

                }
                else
                {
                    panShow.Visible = false;
                    imageField2.Disabled = true;
                }

                dt.Clear();

            }
        }

        //报名
        protected void button5_ServerClick(object sender, EventArgs e)
        {
            if (Request.QueryString["id"] == null || !Utility.Common.IsNumber(Request.QueryString["id"]))
            {
                Response.Redirect("/MatchList.aspx");
            }
            DateTime dt1 = Convert.ToDateTime(hids.Value);
            if (DateTime.Compare(dt1, DateTime.Now) < 0)
            {
                CommonManager.Web.RegJs(this, "alert('抱歉，比赛已开始！');location.href=location.href;", true);
            }
            //判断输入的用户是否正在游戏中
            //BLL.Member mem = new BLL.Member();
            //if (mem.IsInRoomOrGame(UiCommon.UserLoginInfo.UserName))
            //{
            //    Response.Write("<script>alert('要充值的帐号正在游戏中，请先退出游戏再进行充值。');location.href=location.href;</script>");
            //    Response.End();
            //}
            Dictionary<string, object> dic = new Dictionary<string, object>();
            DbSession.Default.FromProc("Web_pApplyMatch").AddInputParameter("@UserID", DbType.Int32, UiCommon.UserLoginInfo.UserID)
                .AddInputParameter("@ContestID", DbType.Int32, Request.QueryString["id"].ToString())
                .AddReturnValueParameter("@ReturnValue", DbType.Int32)
               .Execute(out dic);
            if (dic.Count <= 0)
                CommonManager.Web.RegJs(this, "alert('抱歉，报名失败，可能是服务器繁忙，请稍后再试！');location.href=location.href;", true);
       
            if (dic["ReturnValue"].ToString() == "-1")
            {
                CommonManager.Web.RegJs(this, "alert('抱歉，报名失败，您的" + ConfigurationManager.AppSettings["moneyName"].ToString() + "不足！');location.href=location.href;", true);
            }
            if (dic["ReturnValue"].ToString() == "-2")
            {
                CommonManager.Web.RegJs(this, "alert('已成功报名！');location.href=location.href;", true);
            }
            CommonManager.Web.RegJs(this, "alert('报名成功！');location.href=location.href;", true);
        }
        //退赛
        protected void btnExit_ServerClick(object sender, EventArgs e)
        {
            DateTime dt1 = Convert.ToDateTime(hids.Value);
            if (DateTime.Compare(dt1, DateTime.Now) < 0)
            {
                CommonManager.Web.RegJs(this, "alert('抱歉，比赛已开始，不能退赛！');location.href=location.href;", true);
                return;
            }
            DbSession.Default.FromProc("Web_pExitMatch")
                .AddInputParameter("@UserID", DbType.Int32, UiCommon.UserLoginInfo.UserID)
                .AddInputParameter("@ContestID", DbType.Int32, hide.Value)
                .Execute();
            CommonManager.Web.RegJs(this, "alert('退赛成功！');location.href=location.href;", true);
        }
        public   string   HZ(int   num) 
        { 
            switch(num) 
            { 
            case   1:   return   "一"; 
            case   2:   return   "二"; 
            case   3:   return   "三"; 
            case   4:   return   "四"; 
            case   5:   return   "五"; 
            case   6:   return   "六"; 
            case  7:    return   "七"; 
            case   8:   return   "八"; 
            case   9:   return   "九"; 
            case   10   :return   "十";
            default: return "";
            } 
        }
    }
}
