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
using BCST.Common;
using Bzw.Data;


namespace Bzw.Inhersits.Manage
{
    public partial class Manage_PromotionBalance : UiCommon.ManageBasePage
    {
        /// <summary>
        /// Head1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

        /// <summary>
        /// webmeta1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webmeta1;

        /// <summary>
        /// webtop1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webtop1;

        /// <summary>
        /// Left1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl Left1;

        /// <summary>
        /// webuserlogin1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webuserlogin1;

        /// <summary>
        /// rpLog 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Repeater rpLog;

        /// <summary>
        /// anpPageIndex 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::Wuqi.Webdiyer.AspNetPager anpPageIndex;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;
        protected int PageIndex
        {
            get
            {
                string pi = CommonManager.Web.Request("page", "");
                if (string.IsNullOrEmpty(pi) || !CommonManager.String.IsInteger(pi))
                    return 1;
                return int.Parse(pi);
            }
        }

        public int RowNo = 0;
        /// <summary>
        /// 被推荐玩家成为有效推广后奖励给推广人的金币数
        /// </summary>
        public int Con_ValidUserAddMoney = 0;

        protected void Page_Load(object sender, EventArgs e)
        {
            DataRow dr = BLL.Config.GetInfoOfPromotion();
            if (dr != null)
            {
                Con_ValidUserAddMoney = Convert.ToInt32(dr["Con_ValidUserAddMoney"]);
            }

            if (!IsPostBack)
            {
                BindLog();
            }
        }

        public void BindLog()
        {
            /*
            //DataTable dt = new BLL.Promotion().ListLog(UiCommon.UserLoginInfo.UserID);
            anpPageIndex.RecordCount = (int)DbSession.Default.FromSql( "select count(id) from Web_TuiGuangLog where TG_UserID=" + UiCommon.UserLoginInfo.UserID ).ToScalar();
            anpPageIndex.CurrentPageIndex = PageIndex;

            DataTable dt = DbSession.Default.FromProc("Bzw_GetPager")
                .AddInputParameter( "@QueryStr", DbType.String, "select *,(select t.UserName from TUsers t where t.UserID=tgl.UserID) as UserName from Web_TuiGuangLog tgl where TG_UserID=" + UiCommon.UserLoginInfo.UserID )
                .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
                .AddInputParameter( "@PageCurrent", DbType.Int32, PageIndex )
                .AddInputParameter( "@FdShow", DbType.String, "*" )
                .AddInputParameter( "@FdOrder", DbType.String, "ID desc" )
                .ToDataTable();
		
            rpLog.DataSource = dt;
            rpLog.DataBind();*/
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                .AddInputParameter("@Columns", DbType.String, "*")
                .AddInputParameter("@TableName", DbType.String, "Web_VTGLog")
                .AddInputParameter("@Wheres", DbType.String, " and TG_UserID=" + UiCommon.UserLoginInfo.UserID)
                .AddInputParameter("@KeyName", DbType.String, "ID")
                .AddInputParameter("@OrderBy", DbType.String, "ID desc")
                .ToDataSet();

            if (ds.Tables.Count > 0)
            {
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;

                if (ds.Tables[1].Rows.Count > 0)
                {
                    rpLog.DataSource = ds.Tables[1];
                    rpLog.DataBind();
                }
            }
        }

        public string GetUserPercent(string userId)
        {
            //获取用户总游戏时长
            double playTimeSum = Convert.ToDouble(new BLL.Member().GetPlayTimeSum(userId).Trim());
            if (playTimeSum <= 0)
            {
                return "0%";
            }

            double Con_OnlineTime = 0.0;
            DataRow dr = BLL.Config.GetInfoOfPromotion();
            if (dr == null)
            {
                return "0%";
            }

            //被推广玩家成为有效推广所需要的在线游戏时间
            Con_OnlineTime = Convert.ToDouble(dr["Con_OnlineTime"]);
            Con_OnlineTime = Con_OnlineTime * 60 * 60;//转换成秒数


            if (playTimeSum >= Con_OnlineTime)
            {
                return "100%";
            }
            else
            {
                return (playTimeSum / Con_OnlineTime).ToString("p");
            }
        }
    }

}
