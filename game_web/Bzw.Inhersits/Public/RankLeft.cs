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

namespace Bzw.Inhersits.Public
{
	public partial class Public_RankLeft : System.Web.UI.UserControl
	{
		/// <summary>
		/// Repeater1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater Repeater1;

		/// <summary>
		/// rpList 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater rpList;

		protected void Page_Load(object sender, EventArgs e)
		{
			if (!IsPostBack)
			{
				BindList();
				BindListBattle();
			}
		}

		public void BindList()
		{
			rpList.DataSource = new BLL.Game().ListTGameNameInfo(0).DefaultView;
			rpList.DataBind();
		}


		public void BindListBattle()
		{
			string sql = "select GameName,GameNameID from Web_VGameRoomInfo2 group by GameName,GameNameID";

			Repeater1.DataSource = DbSession.Default.FromSql(sql).ToDataTable(); //new BLL.Game().ListVGameRoomInfo( 0 ).DefaultView;
			Repeater1.DataBind();
		}
	}
}
