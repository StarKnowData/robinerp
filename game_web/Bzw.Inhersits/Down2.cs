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
using Bzw.WebLibrary;
using BLL;

namespace Bzw.Inhersits
{
	public partial class Down2 : UiCommon.BasePage
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
		/// webuserlogin1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webuserlogin1;

		/// <summary>
		/// webservice1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webservice1;

		/// <summary>
		/// webshortcutkey1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		//protected global::Public_WebShortCutKey webshortcutkey1;

		/// <summary>
		/// lteTime 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Literal lteTime;

		/// <summary>
		/// lteCopy 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Literal lteCopy;

		/// <summary>
		/// LteUse 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Literal LteUse;

		/// <summary>
		/// LteSize 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Literal LteSize;

		/// <summary>
		/// lteInfo 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Literal lteInfo;

		/// <summary>
		/// rpGameList 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater rpGameList;

		/// <summary>
		/// webfooter1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webfooter1;

		public string mainImg = string.Empty;
		public string fullUrl = string.Empty;
		public string smallUrl = string.Empty;

		protected void Page_Load( object sender, EventArgs e )
		{
			SeoSetting( SeoConfig.Config.DownPageSeo );
			if( !IsPostBack )
			{
				//---游戏简介类别绑定注释掉，因客户自己在页面中嵌入了静态页面，征得了客户的同意
				BindGameList();
				//BindGameType();
				//添加了代理下载地址,因此注释掉
				DataRow dr = new BLL.Game().GetInfoMain();
				if( dr != null )
				{
					mainImg = dr["Image_URL"].ToString();

					lteTime.Text = dr["Update_Time"].ToString();
					lteCopy.Text = dr["Main_Copy"].ToString();
					LteUse.Text = dr["Main_use"].ToString();
					LteSize.Text = dr["FileSize"].ToString();
					lteInfo.Text = dr["Main_Info"].ToString();

					/*fullUrl = dr["Down_address"].ToString();
					smallUrl = dr["Down_saddress"].ToString();*/

				}
				BLL.Game BllGame = new BLL.Game();
				fullUrl = BllGame.GetDownUrl( "dianxindown" );
				smallUrl = BllGame.GetDownUrl( "wangtongdown" );
			}
		}

		public void BindGameList()
		{
			rpGameList.DataSource = new BLL.Game().List( 0 ).DefaultView;
			rpGameList.DataBind();
		}
		/*public void BindGameType()
		{
			rpGameType.DataSource = new BLL.Game().List(0);
			rpGameType.DataBind();
		}*/
	}
}
