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
	public partial class DaoJu : UiCommon.BasePage
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
		/// rpDaoJu 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater rpDaoJu;

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
			SeoSetting( SeoConfig.Config.PropBuyListSeo );
			if( !IsPostBack )
			{
				BindDaoJu();
			}
		}


		public void BindDaoJu()
		{
			//DataTable dt = new BLL.DaoJu().List(0);
			//rpDaoJu.DataSource = dt.DefaultView;
			//rpDaoJu.DataBind();

			string where = string.Empty;
			int counts;
			DataTable dt = new BLL.DaoJu().PagerList(/*WebPager1.PageSize, WebPager1.CurrentPageIndex,*/ anpPageIndex.PageSize, PageIndex, out counts, " and proptype=0" );

			anpPageIndex.CurrentPageIndex = PageIndex;
			anpPageIndex.RecordCount = counts;
			rpDaoJu.DataSource = dt.DefaultView;
			rpDaoJu.DataBind();
		}
	}

}
