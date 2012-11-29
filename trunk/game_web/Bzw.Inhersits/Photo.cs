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
using Bzw.Entities;
using Bzw.Data;
using Bzw.WebLibrary;

namespace Bzw.Inhersits
{
	public partial class Photo : UiCommon.BasePage
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
		/// rptDataList 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater rptDataList;

		/// <summary>
		/// ltNonData 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Literal ltNonData;

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
				string pi = CommonManager.Web.Request( "page", "1" );
				if( string.IsNullOrEmpty( pi ) || !CommonManager.String.IsInteger( pi ) )
					return 1;
				return int.Parse( pi );
			}
		}

		protected void Page_Load( object sender, EventArgs e )
		{
			SeoSetting( SeoConfig.Config.Userpicture );
			WhereClip where = VUsersAlbum._.Enable == Library.EnableState.通过.ToString() && VUsersAlbum._.IsPublic == Library.PublicState.公开.ToString();

			anpPageIndex.RecordCount = DbSession.Default.Count<VUsersAlbum>( where );
			anpPageIndex.CurrentPageIndex = PageIndex;

			DataTable dt = DbSession.Default.FromProc( "Bzw_GetPager" )
			.AddInputParameter( "@QueryStr", DbType.String, "select * from VUsersAlbum where " + DbSession.Default.Serialization( where ) )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@PageCurrent", DbType.Int32, PageIndex )
			.AddInputParameter( "@FdShow", DbType.String, "*" )
			.AddInputParameter( "@FdOrder", DbType.String, "ShortNum desc,InputTime desc" )
			.ToDataTable();

			if( dt.Rows.Count > 0 )
			{
				rptDataList.Visible = true;
				rptDataList.DataSource = dt;
				rptDataList.DataBind();
				ltNonData.Visible = false;
			}
			else
			{
				rptDataList.Visible = false;
				ltNonData.Visible = true;
			}
		}
	}
}
