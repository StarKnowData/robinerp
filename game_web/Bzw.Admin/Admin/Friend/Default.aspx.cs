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
using Bzw.Entities;
using BCST.Common;

public partial class Admin_Friend_Default : AdminBasePage
{
	protected void Page_Load( object sender, EventArgs e )
	{
		if( !IsPostBack )
		{
			//string action = CommonManager.Web.Request("action",""); //Limit.getFormValue( "action" );
			//string rid = Limit.getFormValue( "params" );

			if( string.IsNullOrEmpty( Action ) || IntParam == 0 )
			{
				btnSubmit.Text = "添加";
				BindData();
				return;
			}

			if( Action == "del" )
			{
				Del(  );
			}
			else if( Action == "delimg" )
			{
				DelImage();
			}
			else if( Action == "edit" )
			{
				btnSubmit.Text = "修改";
				Edit();
			}
		}
	}

	/// <summary>
	/// 修改
	/// </summary>
	private void Edit()
	{
		Web_FriendLink model = DbSession.Default.Get<Web_FriendLink>( Web_FriendLink._.ID == IntParam );
		if( model == null )
			return;
		//赋值
		//if( !string.IsNullOrEmpty( model.ImagePath ) )
		//{
		//    phFileShow.Visible = true;
		//    phFileUpload.Visible = false;
		//    txtImagePath.Value = model.ImagePath;
		//}
		txtLink.Text = model.Link;
		txtOrderID.Text = model.OrderID.ToString();
		txtShortDesc.Text = model.ShortDesc;
		txtTitle.Text = model.Title;
		//CommonManager.Web.SetListControlSelectedFromValue( rdolType, model.Type.ToString() );
		cbxIsEnable.Checked = model.IsEnable;
		BindData();
	}

	/// <summary>
	/// 删除链接图片
	/// </summary>
	private void DelImage()
	{
		Web_FriendLink model = DbSession.Default.Get<Web_FriendLink>( Web_FriendLink._.ID == IntParam );
		if( model == null )
			return;
		CommonManager.File.DeleteFile( model.ImagePath );
		model.ImagePath = "";
		model.Attach();
		DbSession.Default.Save<Web_FriendLink>( model );
	}

	/// <summary>
	/// 删除
	/// </summary>
	private void Del(  )
	{
		Web_FriendLink model = DbSession.Default.Get<Web_FriendLink>(Web_FriendLink._.ID == IntParam);
		if( model == null )
			return;
		CommonManager.File.DeleteFile(model.ImagePath);
		DbSession.Default.Delete<Web_FriendLink>( model );
		CommonManager.Web.ResponseEnd("Default.aspx",true);
	}

	/// <summary>
	/// 绑定数据
	/// </summary>
	private void BindData()
	{
		#region oldcode
		//DbSession.Default.CacheOn();

		//anpPageIndex.RecordCount = DbSession.Default.Count<Web_FriendLink>( new WhereClip( "" ) );
		//anpPageIndex.CurrentPageIndex = PageIndex;

		//DataTable dt = DbSession.Default.FromProc( "Bzw_GetPager" )
		//    .AddInputParameter("@QueryStr", DbType.String, "Web_FriendLink") //如果有条件，表和视图这样写"select * from Web_FriendLink where " + new WhereClip( "" )
		//    .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
		//    .AddInputParameter( "@PageCurrent", DbType.Int32, PageIndex )
		//    .AddInputParameter( "@FdShow", DbType.String, "*" )
		//    .AddInputParameter( "@FdOrder", DbType.String, "OrderID desc,InputTime desc" )
		//    .ToDataTable();

		//if( dt.Rows.Count <= 0 )
		//{
		//    this.NoUserList.Visible = true;
		//}
		//else
		//{
		//    rptDataList.DataSource = dt;
		//    rptDataList.DataBind();
		//}
		#endregion

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
			.AddInputParameter( "@Columns", DbType.String, "*" )
			.AddInputParameter( "@TableName", DbType.String, "Web_FriendLink" )
			.AddInputParameter( "@Wheres", DbType.String, "" )
			.AddInputParameter( "@KeyName", DbType.String, "ID" )
			.AddInputParameter( "@OrderBy", DbType.String, "ID desc" )
			.ToDataSet();

		if( ds.Tables.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			if( ds.Tables[1].Rows.Count > 0 )
			{
				rptDataList.Visible = true;
				rptDataList.DataSource = ds.Tables[1];
				rptDataList.DataBind();
				NoUserList.Visible = false;
			}
			else
			{
				NoUserList.Visible = true;
				rptDataList.Visible = false;
			}
		}
	}

	protected void btnSubmit_Click( object sender, EventArgs e )
	{
		//提交
		if( !IsValid )
			return;
		Web_FriendLink model;
		//string action = CommonManager.Web.Request("") //Limit.getFormValue( "action" );
		//string rid = Limit.getFormValue( "params" );
		if( Action == "edit" )
		{
			model = DbSession.Default.Get<Web_FriendLink>( Web_FriendLink ._.ID == IntParam );
			model.Attach();
		}
		else
		{
			model = new Web_FriendLink();
			model.InputTime = DateTime.Now;
		}
		string lcover = "";
		if( Request.Files.Count > 0 )
		{
			try
			{
				if( !CommonManager.File.UploadFile( Request.Files["fileImagePath"], 3 * 1024 * 1024, new string[] { "jpg", "jpeg", "gif", "bmp", "png" }, "/Upload/Friend", FileOperator.RenameType.流水号, out lcover ) )
				{
					lcover = "";
				}
			}
			catch( Exception ex )
			{
				//lcover = "";
                throw new Exception(ex.Message+ex.StackTrace);
			}
		}
		model.ImagePath = string.IsNullOrEmpty( model.ImagePath ) ? lcover : model.ImagePath;
		model.IsEnable = cbxIsEnable.Checked;
		model.Link =  txtLink.Text.Trim().StartsWith("http://")  ? txtLink.Text.Trim() : "http://" + txtLink.Text.Trim();
		model.OrderID = ( string.IsNullOrEmpty( txtOrderID.Text.Trim() ) || !CommonManager.String.IsInteger( txtOrderID.Text.Trim() ) ) ? 1 : int.Parse(txtOrderID.Text.Trim());
		model.ShortDesc = txtShortDesc.Text.Trim();
		model.Title = txtTitle.Text.Trim();
		model.Type = 0;// int.Parse( rdolType.SelectedItem.Value );

		DbSession.Default.Save<Web_FriendLink>( model );

		CommonManager.Web.ResponseEnd( "Default.aspx", true );
	}
}
