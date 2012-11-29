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
using Bzw.Data;
using Bzw.WebLibrary;

namespace Bzw.Inhersits
{
	public partial class BattleRank : UiCommon.BasePage
	{
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
		/// webuserlogin1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webuserlogin1;

		/// <summary>
		/// rankleft1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>

		protected global::System.Web.UI.UserControl webservice1;

		/// <summary>
		/// rpList 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater rpList;

		/// <summary>
		/// webfooter1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webfooter1;

		protected string BattleRoomName = "";

		protected void Page_Load(object sender, EventArgs e)
		{
			SeoSetting(SeoConfig.Config.RankSeo);
			BindList();
		}

		public void BindList()
		{
			string where = string.Empty;
			string queryString = string.Empty;

			string id = Utility.Common.SqlEncode(Utility.Common.GetStringOfUrl("id"));
			//string roomId = Utility.Common.SqlEncode( Utility.Common.GetStringOfUrl( "rid" ) );
			if (!string.IsNullOrEmpty(id))
			{
				if (!Utility.Common.IsNumber(id))
				{
					Response.Write("请不要非法操作");
					Response.End();
				}
				where += " and NameID=" + id; //+ " and roomid=" + roomId;
				//queryString += "&id=" + id + "&name=" + Server.UrlEncode( Utility.Common.GetStringOfUrl( "name" ) );
			}
			else
			{
				DataTable dts = DbSession.Default.FromSql("select top 1 * from Web_VGameRoomInfo2").ToDataTable();
				if (dts.Rows.Count > 0)
				{
					where = " and NameID=" + dts.Rows[0]["GameNameID"].ToString(); //+ " and roomid=" + dts.Rows[0]["roomid"].ToString();
					//queryString = "&id=" + dts.Rows[0]["GameNameID"].ToString() + "&name=" + Server.UrlEncode( dts.Rows[0]["BattleRoomName"].ToString() );
					BattleRoomName = dts.Rows[0]["BattleRoomName"].ToString();
				}
			}
            if (ConfigurationManager.AppSettings["RobotRank"] != null && ConfigurationManager.AppSettings["RobotRank"] == "0")
            {
                where += " and userid in (select userid from tusers where isrobot=0)";
            }
			int counts;
			DataTable dt = new BLL.Member().PagerListBattlePoint(50, 1, out counts, where);
			//WebPager1.ItemCount = counts;
			//WebPager1.UrlQueryString = queryString;
			//Rowid = WebPager1.CurrentPageIndex * WebPager1.PageSize - WebPager1.PageSize;
			rpList.DataSource = dt.DefaultView;
			rpList.DataBind();
		}
	}
}
