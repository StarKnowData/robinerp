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


namespace Bzw.Inhersits
{
	public partial class Promoter : UiCommon.BasePage
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
		/// rpNewZhiNan 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater rpNewZhiNan;

		/// <summary>
		/// objDataZhiNan 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.ObjectDataSource objDataZhiNan;

		/// <summary>
		/// webservice1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webservice1;

		/// <summary>
		/// webfooter1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webfooter1;
		public string NewTitle = string.Empty;
		public string NewContent = string.Empty;
		public string Hits = string.Empty;
		public string AddTime = string.Empty;

		BLL.News news = new BLL.News();

		protected void Page_Load( object sender, EventArgs e )
		{

			if( !IsPostBack )
			{
				BindNew();
			}
		}

		public void BindNew()
		{
			DataRow dr = null;
			string id = Utility.Common.SqlEncode( Utility.Common.GetStringOfUrl( "id" ) );
			if( string.IsNullOrEmpty( id ) )
			{
				dr = news.GetInfoByTitle( "推广员介绍" );
			}
			else
			{
				dr = news.GetInfo( id );
			}
			if( dr != null )
			{
				NewTitle = dr["Title"].ToString();
				NewContent = dr["Content"].ToString();
				Hits = dr["Hits"].ToString();
				AddTime = ( (DateTime)dr["Issue_Time"] ).ToString( "yyyy年MM月dd日" );

				string seoDesc = Utility.Common.ClearHtml( Utility.Common.CutStringUnicode( NewContent, 300, "..." ) );

				SeoNewsSetting( NewTitle, dr["Keywords"].ToString(), seoDesc );
			}


		}
	}
}
