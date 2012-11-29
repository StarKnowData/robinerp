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

namespace Bzw.Inhersits.UserInfo
{
	public partial class UserInfo_PhotoList : UiCommon.BasePage
	{
		/// <summary>
		/// webtop1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webtop1;

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
		/// rptAlbumColumnList 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater rptAlbumColumnList;

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

		protected string UserName = "";
		protected string AlbumName = "";
		protected string uid = "";

		protected int IntParam
		{
			get
			{
				string tmp = CommonManager.Web.Request( "params", "" );
				if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
					return 0;
				return int.Parse( tmp );
			}
		}

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
			if( IntParam == 0 )
				return;
            SeoSetting(SeoConfig.Config.DefaultSeo);
			Web_UserAlbumColumn album = DbSession.Default.Get<Web_UserAlbumColumn>( Web_UserAlbumColumn._.ID == IntParam );
			if( album == null || album.IsPublic == Library.PublicState.隐藏.ToString() )
				return;

			TUsers user = DbSession.Default.Get<TUsers>( TUsers._.UserID == album.UserID );
			if( user == null )
				return;

			AlbumName = album.AlbumName;
			UserName = user.NickName;//user.UserName;
			uid = user.UserID.ToString();

			WhereClip where = VUsersAlbum._.ColumnID == IntParam && VUsersAlbum._.Enable == Library.EnableState.通过.ToString();

			anpPageIndex.RecordCount = DbSession.Default.Count<VUsersAlbum>( where );
			anpPageIndex.CurrentPageIndex = PageIndex;
			//anpPageIndex.PageSize = 4;

			DataTable dt = DbSession.Default.FromProc( "Bzw_GetPager" )
				.AddInputParameter( "@QueryStr", DbType.String, "select * from VUsersAlbum where " + string.Format( where.ToString(), "", "" ) )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@PageCurrent", DbType.Int32, PageIndex )
			.AddInputParameter( "@FdShow", DbType.String, "*" )
			.AddInputParameter( "@FdOrder", DbType.String, "ShortNum desc,InputTime desc" )
			.ToDataTable();

			if( dt.Rows.Count > 0 )
			{
				rptAlbumColumnList.Visible = true;
				rptAlbumColumnList.DataSource = dt;
				rptAlbumColumnList.DataBind();
				ltNonData.Visible = false;
			}
			else
			{
				rptAlbumColumnList.Visible = false;
				ltNonData.Visible = true;
			}
		}
	}
}
