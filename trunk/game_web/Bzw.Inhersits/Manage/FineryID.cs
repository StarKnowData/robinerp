using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;
using Bzw.WebLibrary;

namespace Bzw.Inhersits.Manage
{

    public partial class Manage_FineryID : UiCommon.BasePage
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
		/// Control1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl Control1;

		/// <summary>
		/// Control2 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl Control2;

		/// <summary>
		/// Left1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl Left1;

		/// <summary>
		/// FineryIDTop 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater FineryIDTop;

		/// <summary>
		/// NoProTop 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Label NoProTop;

		/// <summary>
		/// FineryIDList 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater FineryIDList;

		/// <summary>
		/// NoProList 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Label NoProList;

		/// <summary>
		/// anpPageIndex 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::Wuqi.Webdiyer.AspNetPager anpPageIndex;

		/// <summary>
		/// webfooter1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webfooter1;
		public string where = @" and IsBuy=0 and IsSale=1";
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
            SeoSetting(SeoConfig.Config.DefaultSeo);
			string seacid = CommonManager.Web.Request( "seachid", "" );
			if( ( !string.IsNullOrEmpty( seacid ) && !Utility.Common.IsNumber( seacid ) ) || ( !string.IsNullOrEmpty( seacid ) && seacid.Trim().Length < 3 ) )
			{
				Utility.Common.OutMsgBox( "搜索的靓号须为3-9位数字", "" );
			}
			//获取搜索条件
			if( !string.IsNullOrEmpty( seacid ) || seacid != "" )
			{
				where += "and FineryID like '%" + seacid + "%'";
			}
			string type = CommonManager.Web.Request( "type", "" );
			if( type == "aabb" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(\\d)\\1{1,}(\\d)\\2{1,}') = 1 and dbo.regex_ismatch(FineryID,'(\\d)\\1{1}(\\d)\\2{1}(\\d)\\3{1}') = 0";
			}
			if( type == "aabbcc" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(\\d)\\1{1}(\\d)\\2{1}(\\d)\\3{1}') = 1";
			}
			if( type == "abab" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(([\\d]){2})\\1{1}') = 1 and dbo.regex_ismatch(FineryID,'(\\d)\\1{1,}(\\d)\\2{1,}') = 0";
			}
			if( type == "ababab" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(([\\d]){2})\\1{2}') = 1 ";
			}
			if( type == "abcabc" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(([\\d]){3})\\1{1}') = 1";
			}
			if( type == "abgab" )
			{
				where += "and dbo.regex_ismatch(FineryID,'^((\\d){2,})\\d\\1{1}$') = 1";
			}
			if( type == "3a" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(\\d)\\1{2}')=1 and dbo.regex_ismatch(FineryID,'(\\d)\\1{3,}')= 0";
			}
			if( type == "4a" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(\\d)\\1{3}')=1 and dbo.regex_ismatch(FineryID,'(\\d)\\1{4,}')= 0";
			}
			if( type == "5a" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(\\d)\\1{4,}')=1";
			}
			if( type == "4sun" )
			{
				where += "and dbo.regex_ismatch(FineryID,'((?:0(?=1)|1(?=2)|2(?=3)|3(?=4)|4(?=5)|5(?=6)|6(?=7)|7(?=8)|8(?=9)){3}\\d)|((?:9(?=8)|8(?=7)|7(?=6)|6(?=5)|5(?=4)|4(?=3)|3(?=2)|2(?=1)|1(?=0)){3}\\d)')=1";
			}
			if( type == "date" )
			{
				where += "and dbo.regex_ismatch(FineryID,'(19|20)[\\d]{2}((1[0-2])|(0[1-9]))((3[0-1])|(2[0-9])|(1[0-9])|(0[1-9]))')=1";
			}
			if( !IsPostBack )
			{
				BindFineryID();
				BindFineryIDTop();
			}
		}

		//绑定符合搜索条件靓号
		public void BindFineryID()
		{
			DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
				.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
				.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
				.AddInputParameter( "@Columns", DbType.String, "*" )
				.AddInputParameter( "@TableName", DbType.String, "Web_FineryID" )
				.AddInputParameter( "@Wheres", DbType.String, where )
				.AddInputParameter( "@KeyName", DbType.String, "DateTime" )
				.AddInputParameter( "@OrderBy", DbType.String, "DateTime desc" )
				.ToDataSet();

			if( ds.Tables.Count > 0 )
			{
				anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
				anpPageIndex.CurrentPageIndex = PageIndex;

				if( ds.Tables[1].Rows.Count > 0 )
				{
					this.FineryIDList.Visible = true;
					this.NoProList.Visible = false;
					this.FineryIDList.DataSource = ds.Tables[1];
					this.FineryIDList.DataBind();
				}
				else
				{
					this.NoProList.Visible = true;
					this.FineryIDList.Visible = false;
				}
			}
		}

		//绑定推荐ID
		public void BindFineryIDTop()
		{
			string sql = "select top 9 FineryID,Price from Web_FineryID where IsTop=1 and IsBuy=0 and IsSale=1";
			DataTable tb = DbSession.Default.FromSql( sql ).ToDataTable();
			if( tb.Rows.Count > 0 )
			{
				this.FineryIDTop.Visible = true;
				this.NoProTop.Visible = false;
				this.FineryIDTop.DataSource = tb;
				this.FineryIDTop.DataBind();
			}
			else
			{
				this.FineryIDTop.Visible = false;
				this.NoProTop.Visible = true;
			}
		}
	}
}
