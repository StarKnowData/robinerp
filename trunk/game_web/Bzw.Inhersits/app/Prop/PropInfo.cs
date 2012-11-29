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
using System.Text;
using BCST.Common;
using Bzw.Data;

namespace Bzw.Inhersits
{
    public partial class PropInfo : UiCommon.ManageBasePage
    {
        /// <summary>
        /// rpList 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Repeater rpList;

        public int PageSize = 4;
    //    public int CurrentNum = 1;
        public int MaxPage = 999;

        public string PropID = string.Empty;
        public string PropName = string.Empty;
        public string PropPrice = string.Empty;
        public string PropVipPrice = string.Empty;
        public string PropDescript = string.Empty;
        public string PropImg = "1";
        public string bgColor = string.Empty;
        public bool IsVip = false;
        public string UserPropCount = string.Empty;
        protected void Page_Load(object sender, EventArgs e)
        {
            PropID = CommonManager.Web.Request("propid", "");
            bgColor = CommonManager.Web.Request("bgcolor", "cccccc");
            //取当前页码
            //if (Request["num"] != null)
            //{
            //    CurrentNum = Convert.ToInt32(Request["num"]);
            //}
            if (!IsPostBack)
            {
                string sql = "select * from TPropDefine where PropID=@PropID";
                DataTable dt = DbSession.Default.FromSql(sql)
                    .AddInputParameter("@PropID", DbType.Int32, PropID)
                    .ToDataTable();
                if (dt.Rows.Count > 0)
                {
                    //取第一行数据
                    PropImg = dt.Rows[0]["PropID"].ToString();
                    PropName = dt.Rows[0]["PropName"].ToString();
                    PropPrice = dt.Rows[0]["Price"].ToString();
                    PropVipPrice = dt.Rows[0]["VipPrice"].ToString();
                    PropDescript = dt.Rows[0]["Descript"].ToString();
                    PropImg = PropID;//

                    //绑定数据
                    /*rpList.DataSource = dt.DefaultView;
                    rpList.DataBind();*/
                }
                try
                {
                    UserPropCount = DbSession.Default.FromSql("select ISNULL(holdcount,0) from TUserProp where userid=" + UiCommon.UserLoginInfo.UserID + " and propid=" + PropID).ToScalar().ToString();
                }
                catch { UserPropCount = "0"; }
                
         //   BindVip();
            }
        }
        public string GetBgColor()
        {
            if (Request["bgcolor"] != null && Request["bgcolor"].ToString().Trim().Length > 0)
            {
                return Request["bgcolor"].ToString();
            }

            return "ffeccd";
        }

        //判断用户是否是vip
        public void BindVip()
        {
            string VipTime2;
            DataRow dr = new BLL.Member().GetInfoInTUserInfo(UiCommon.UserLoginInfo.UserID);
            if (dr != null)
            {
                VipTime2 = dr["VipTime2"].ToString();
                DateTime dtInit = new DateTime(1970, 01, 01, 08, 00, 00);
                DateTime dtNow = DateTime.Now;

                if (Convert.ToDateTime(VipTime2) > dtInit)
                {
                    if (dtNow <= Convert.ToDateTime(VipTime2))
                    {
                        IsVip = true;
                    }
                }
            }
        }
        public void DaojuList()
        {
            #region 旧将所有道具都读出的代码
            /*//记录总数
			string sql = "select count(PropID) from TPropDefine";
			int rsCount = Convert.ToInt32( Utility.SqlHelper.ExecuteScalar( CommandType.Text, sql, null ) );
			//取当前页码
			if( Request["page"] != null )
			{
				CurrentPage = Convert.ToInt32( Request["page"] );
			}
			//最大页数
			if( rsCount % PageSize == 0 )
			{
				MaxPage = rsCount / PageSize;
			}
			else
			{
				MaxPage = Convert.ToInt32( Math.Floor( Convert.ToDouble( rsCount / PageSize ) ) ) + 1;
			}
			//Response.Write("<br>" + MaxPage);

			//取当前页数据
			if( CurrentPage == 1 )
			{
				sql = "select top " + PageSize + " * from TPropDefine order by PropID";
			}
			else if( CurrentPage > 1 && CurrentPage < MaxPage )
			{
				sql = "select top " + PageSize + " * from TPropDefine where PropID not in(select top " + ( PageSize * ( CurrentPage - 1 ) ) + " PropID from TPropDefine order by PropID) order by PropID";
			}
			else if( CurrentPage >= MaxPage )
			{
				CurrentPage = MaxPage;
				sql = "select * from TPropDefine where PropID not in(select top " + ( PageSize * ( CurrentPage - 1 ) ) + " PropID from TPropDefine order by PropID) order by PropID";
			}
			//Response.Write("<br>"+sql);*/
            #endregion



        }

    }
}
