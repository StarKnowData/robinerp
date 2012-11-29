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
using Bzw.Entities;
using Bzw.WebLibrary;

namespace Bzw.Inhersits.UserInfo
{
	public partial class UserInfo_Album : UiCommon.BasePage
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

		public string usernickname = string.Empty;
		protected string un
		{
			get
			{
				return Server.HtmlEncode( CommonManager.Web.RequestUrlDecode( "params", "" ) );
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
          
			if( string.IsNullOrEmpty( un ) )
				return;
            SeoSetting(SeoConfig.Config.DefaultSeo);
			//TUsers user = DbSession.Default.Get<TUsers>(TUsers._.UserName == un);
			TUsers user = DbSession.Default.Get<TUsers>( TUsers._.UserID == un );

			if( user == null )
				return;

			//绑定用户公开的相册列表
			//string where = " where UserID=" + user.UserID;
			usernickname = user.NickName;
			WhereClip where = Web_vUserAlbumColumn._.UserID == user.UserID && Web_vUserAlbumColumn._.IsPublic == Library.PublicState.公开.ToString();

			anpPageIndex.RecordCount = DbSession.Default.Count<Web_vUserAlbumColumn>( where );
			anpPageIndex.CurrentPageIndex = PageIndex;
			//anpPageIndex.PageSize = 4;

			DataTable dt = DbSession.Default.FromProc( "Bzw_GetPager" )
				.AddInputParameter( "@QueryStr", DbType.String, "select * from Web_vUserAlbumColumn where " + string.Format( where.ToString(), "", "" ) )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@PageCurrent", DbType.Int32, PageIndex )
			.AddInputParameter( "@FdShow", DbType.String, "*" )
			.AddInputParameter( "@FdOrder", DbType.String, "OrderID desc,InputTime desc" )
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

		protected string GetPicCount( int albumID )
		{
			if( albumID == 0 )
				return "";
			return DbSession.Default.Count<Web_UserAlbum>( Web_UserAlbum._.ColumnID == albumID ).ToString();
		}
	}
}
