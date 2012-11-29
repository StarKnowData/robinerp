using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;
using BCST.Common;
using System.Data;
using Bzw.Data;

  public partial class Admin_Users_UserReceiveMoneyList : AdminBasePage
    {
        public int rowid = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                AdminPopedom.IsHoldModel("09");
                BindRecord();
            }
        }
        public void BindRecord()
        {
            StringBuilder where = new StringBuilder(); //查询条件构造函数

            #region 设置搜索条件
            string key = CommonManager.Web.RequestUrlDecode("key", "");  //获取从URL中传过来的值
            string bd = CommonManager.Web.RequestUrlDecode("bd", "");
            string ed = CommonManager.Web.RequestUrlDecode("ed", "");


            //搜索用户名
            if (!string.IsNullOrEmpty(key))  //如果用户名不为空
                where.AppendFormat(" and UserName='{0}'", key);   //将用户名拼成查询条件

            //按时间段搜索
            if (!string.IsNullOrEmpty(bd) && CommonManager.String.IsDateTime(bd))  //如果开始时间不为空
            {
                where.AppendFormat(" and LastReceiveTime>='{0} 00:00:00' ", bd);  //将开始时间格式化后拼成查询条件
            }

            if (!string.IsNullOrEmpty(ed) && CommonManager.String.IsDateTime(ed))
            {
                where.AppendFormat(" and LastReceiveTime<dateadd(day,1,'{0} 00:00:00') ", ed);
            }


            #endregion

            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")    //执行分页的存储过程
                .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)  //当前页码显示的数据
                .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)  //页码的索引
                .AddInputParameter("@Columns", DbType.String, "*")          //需要获取哪些列
                .AddInputParameter("@TableName", DbType.String, "Web_VReceiveMoneyLog")  //表或视图的名称
                .AddInputParameter("@Wheres", DbType.String, where.ToString())  //查询条件
                .AddInputParameter("@KeyName", DbType.String, "LastReceiveTime")     //设置主键的名称
                .AddInputParameter("@OrderBy", DbType.String, "LastReceiveTime desc")  //设置排序的字段
                .ToDataSet();                                        //执行数据查询语句

            if (ds.Tables.Count > 0)
            {

                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0]; //获取总的记录条数
                anpPageIndex.CurrentPageIndex = PageIndex;   //  获取页码的索引
                if (ds.Tables[1].Rows.Count > 0)
                {
                    rptDataList.DataSource = ds.Tables[1];  //获取数据表中的数据
                    rptDataList.DataBind();       //将数据绑定到分页空间上
                    rptDataList.Visible = true;  //设置分页控件可不可用
                    ltNonData.Visible = false;  //设置要不要显示 “无记录语句”
                }
                else
                {
                    rptDataList.Visible = false;
                    ltNonData.Visible = true;
                }
            }


        }
    }
