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
using Bzw.WebLibrary;


namespace Bzw.Inhersits
{
	public partial class NewsList : UiCommon.BasePage
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
		/// form1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlForm form1;

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
		/// rpNewType 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater rpNewType;

		/// <summary>
		/// webservice1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webservice1;

		/// <summary>
		/// rpNewsList 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater rpNewsList;

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
		public string location = string.Empty;
		BLL.News news = new BLL.News();

		private int PageIndex
		{
			get
			{
				string tmp = CommonManager.Web.Request( "page", "" );
				if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
					return 1;
				return int.Parse( tmp );
			}
		}

		protected void Page_Load( object sender, EventArgs e )
		{
			SeoSetting( SeoConfig.Config.NewsListSeo );
			if( !IsPostBack )
			{
			//	BindNewType();
			}

			BindNewList();
		}

		public void BindNewType()
		{
			rpNewType.DataSource = news.TypeList().DefaultView;
			rpNewType.DataBind();
		}

		public void BindNewList()
		{
			string where = string.Empty;
			string queryString = string.Empty;

			string tid = Utility.Common.SqlEncode( Utility.Common.GetStringOfUrl( "tid" ) );
			if( !string.IsNullOrEmpty( tid ) )
			{
				if( !Utility.Common.IsNumber( tid ) )
				{
					Response.Write( "请不要非法操作" );
					Response.End();
				}
				else
				{
					where += " and News_Type=" + tid + " ";
					queryString += "&tid=" + Server.UrlEncode( queryString );
					location = "<a href=\"/NewsList.aspx\">新闻中心</a> > " + new BLL.News().GetTypeName( tid );
				}
			}
			else
			{

				location = "新闻中心";

			}

			int counts;
			DataTable dt = new BLL.News().PagerList_Lsl(/*WebPager1.PageSize, WebPager1.CurrentPageIndex,*/ anpPageIndex.PageSize, PageIndex, out counts, where );
			//WebPager1.ItemCount = counts;
			anpPageIndex.CurrentPageIndex = PageIndex;
			anpPageIndex.RecordCount = counts;
			//WebPager1.UrlQueryString = queryString;
			rpNewsList.DataSource = dt.DefaultView;
			rpNewsList.DataBind();
		}
	}
}
