#pragma once
#ifndef __UTILS__H__
#define __UTILS__H__
#include"..\include\Package.h"
#include"..\include\ComplexMat.h"
#include<fstream>
#include<iostream>
#include<string>
#include"..\include\sar_comm.h"


/*********************************************************/
/*                Delaunay三角网 节点类                  */
/*********************************************************/
class InSAR_API tri_node
{
public:
	/*默认构造函数*/
	tri_node();
	/*拷贝构造函数*/
	tri_node(const tri_node& node);
	/*构造函数
	* 参数1 节点行数
	* 参数2 节点列数
	* 参数3 节点邻接边数
	* 参数4 节点相位
	*/
	tri_node(int, int, int, double);
	~tri_node();
	/*赋值函数（深拷贝赋值）*/
	tri_node operator = (const tri_node& src);
	/*获取节点相位
	* 参数1 相位指针（返回值）
	*/
	int get_phase(double* phi) const;
	/*获取节点行列坐标
	* 参数1 行序号
	* 参数2 列序号
	*/
	int get_pos(int* rows, int* cols) const;
	/*节点相位赋值
	* 参数1 输入相位
	*/
	int set_phase(double phi);
	/*获取邻接边指针
	* 参数1 指向邻接边指针的指针（返回值）
	* 参数2 邻接边个数指针（返回值）
	*/
	int get_neigh_ptr(long** ptr2ptr, int* num) const;
	/*改变解缠状态
	* 参数1 是否已经解缠
	*/
	int set_status(bool b_unwrapped);
	/*改变平衡状态
	* 参数1 是否属于残差平衡三角形
	*/
	int set_balance(bool b_balanced);
	/*打印邻接边序号
	* 
	*/
	int print_neighbour() const;
	/*获取邻接边个数
	* 参数1 邻接边个数指针
	*/
	int get_num_neigh(int* num_neigh) const;
	/*获取与另一节点的距离
	* 参数1 另一节点
	* 参数2 距离
	*/
	int get_distance(tri_node node, double* distance) const;
	/*获取解缠状态
	* 返回值（是否已解缠）
	*/
	bool get_status() const;
	/*获取平衡状态
	* 返回值（是否平衡，默认是）
	*/
	bool get_balance() const;
	/*返回是否节点属于残差三角形
	*/
	bool is_residue_node() const;
	/*设置节点是否属于残差节点
	*/
	int set_residue(bool b_res);
	/*获取形变速率*/
	double get_vel() const;
	/*获取高程误差*/
	double get_height() const;
	/*设置形变速率*/
	int set_vel(double vel);
	/*设置高程误差*/
	int set_height(double height);

private:

	/*****************InSAR处理变量*******************/

	/*是否已解缠(默认未解缠)*/
	bool b_unwrapped;
	/*是否属于残差节点*/
	bool b_residue;
	/*是否属于平衡三角形的顶点（默认为是），同时在PS-InSAR中充当是否节点被丢弃的标志(为true表示不被丢弃， 为false表示被丢弃)*/
	bool b_balanced;
	/*节点行数（起始值为0）*/
	int rows;
	/*节点列数（起始值为0）*/
	int cols;
	/*节点邻接边数*/
	int num_neigh_edges;
	/*节点相位*/
	double phase;
	/*节点邻接边序号*/
	long* neigh_edges;

	/*****************PS-InSAR处理变量*******************/
	
	/*形变速率*/
	double vel;
	/*高程误差*/
	double epsilon_height;
};

/*********************************************************/
/*             Delaunay三角网 三角形结构体               */
/*********************************************************/
struct triangle
{
	/*三角形序号*/
	int num;
	/*点1*/
	int p1;
	/*点2*/
	int p2;
	/*点3*/
	int p3;
	/*三角形残差值*/
	double residue;
	/*相邻三角形序号1*/
	int neigh1;
	/*相邻三角形序号2*/
	int neigh2;
	/*相邻三角形序号3*/
	int neigh3;
	/*边1（从1开始）*/
	int edge1;
	/*边2（从1开始）*/
	int edge2;
	/*边3（从1开始）*/
	int edge3;

	/*默认构造函数*/
	triangle()
	{
		num = p1 = p2 = p3 = neigh1 = neigh2 = neigh3 = edge1 = edge2 = edge3 = 0;
		residue = 0.0;
	}
	/*拷贝构造函数*/
	triangle(const triangle& cp)
	{
		this->edge1 = cp.edge1;
		this->edge2 = cp.edge2;
		this->edge3 = cp.edge3;
		this->neigh1 = cp.neigh1;
		this->neigh2 = cp.neigh2;
		this->neigh3 = cp.neigh3;
		this->num = cp.num;
		this->p1 = cp.p1; this->p2 = cp.p2; this->p3 = cp.p3;
		this->residue = cp.residue;
	}
	/*赋值(深拷贝)*/
	triangle operator= (const triangle& cp)
	{
		this->edge1 = cp.edge1;
		this->edge2 = cp.edge2;
		this->edge3 = cp.edge3;
		this->neigh1 = cp.neigh1;
		this->neigh2 = cp.neigh2;
		this->neigh3 = cp.neigh3;
		this->num = cp.num;
		this->p1 = cp.p1; this->p2 = cp.p2; this->p3 = cp.p3;
		this->residue = cp.residue;
		return *this;
	}
};


/*********************************************************/
/*             Delaunay三角网 三角形边结构体             */
/*********************************************************/
struct tri_edge
{
	/**********InSAR变量**********/

	/*积分增益（序号从小到大为正）*/
	double gain;
	/*相位质量（用于质量图法解缠）*/
	double quality;
	/*边序列号*/
	int num;
	/*端点1*/
	int end1;
	/*端点2*/
	int end2;
	/*残差边标志*/
	bool isResidueEdge;
	/*网络边界标志*/
	bool isBoundry;


	/**********PS_InSAR变量**********/

	/*线性形变速度差系数（4 * pi / lambda * Ti）*/
	//double coef_delta_vel;
	/*高程误差系数（4 * pi * bperp_i / lambda / R_i / sin_theta_i  ）*/
	//double coef_delta_height;
	/*线性形变速度差(定义为大坐标 - 小坐标)*/
	double delta_vel;
	/*高程误差(定义为大坐标 - 小坐标)*/
	double delta_height;
	/*模型相干系数*/
	double MC;
	/*端点相位差（相位差定义为：大序号端点减小序号端点）*/
	double phase_diff;

	/*默认构造函数*/
	tri_edge() {
		gain = 0.0;
		quality = 0.0;
		num = 0;
		end1 = 0; end2 = 0;
		isResidueEdge = false;
		isBoundry = false;
		delta_vel = 0.0;
		delta_height = 0.0; MC = 0.0; phase_diff = 0.0;
	}
	/*拷贝构造函数*/
	tri_edge(const tri_edge& cp)
	{
		gain = cp.gain;
		quality = cp.quality;
		num = cp.num;
		end1 = cp.end1; end2 = cp.end2;
		isResidueEdge = cp.isResidueEdge;
		isBoundry = cp.isBoundry;
		delta_vel = cp.delta_vel;
		delta_height = cp.delta_height; MC = cp.MC; phase_diff = cp.phase_diff;
	}
	/*赋值函数（深拷贝赋值）*/
	tri_edge operator = (const tri_edge& cp)
	{
		gain = cp.gain;
		quality = cp.quality;
		num = cp.num;
		end1 = cp.end1; end2 = cp.end2;
		isResidueEdge = cp.isResidueEdge;
		isBoundry = cp.isBoundry;
		delta_vel = cp.delta_vel;
		delta_height = cp.delta_height; MC = cp.MC; phase_diff = cp.phase_diff;
		return *this;
	}
};

/*********************************************************/
/*          Delaunay三角网 三角形边序列号结构体          */
/*********************************************************/
struct edge_index
{
	double quality;
	int num;
	edge_index() { num = 0; quality = 0.0; }
	friend bool operator < (struct edge_index a, struct edge_index b)
	{
		return a.quality > b.quality;
	}
	
};

/*-------------------------------------------------------*/
/*                   规则网格节点结构体                  */
/*-------------------------------------------------------*/
struct node_index
{
	/*节点行数（从0开始）*/
	int row;
	/*节点列数（从0开始）*/
	int col;
	/*节点相位质量*/
	double quality;
	/*默认构造函数*/
	node_index()
	{
		row = 0; col = 0; quality = 0.0;
	}
	/*拷贝构造函数*/
	node_index(const node_index& cp)
	{
		this->row = cp.row; this->col = cp.col; this->quality = cp.quality;
	}
	/*赋值函数*/
	node_index operator = (const node_index& cp)
	{
		this->row = cp.row; this->col = cp.col; this->quality = cp.quality;
		return *this;
	}
	friend bool operator < (struct node_index a, struct node_index b)
	{
		return a.quality > b.quality;
	}
};




/*********************************************************/
/*               干涉SAR处理基本函数类库                 */
/*********************************************************/
class InSAR_API Utils
{
public:
	Utils();
	~Utils();
	/*@brief 生成范德蒙矩阵
	* @param inArray                           自变量序列
	* @param vandermondeMatrix                 范德蒙矩阵
	* @param degree                            阶数
	* @return 成功返回-1，否则返回0
	*/
	static int createVandermondeMatrix(
		Mat& inArray,
		Mat& vandermondeMatrix,
		int degree
	);
	/*@brief 多项式拟合（Ax=b）
	* @param A
	* @param b
	* @param x
	*/
	static int ployFit(
		Mat& A,
		Mat& b,
		Mat& x
	);
	/*@brief polyVal
	* @param coefficient
	* @param x
	* @param val
	*/
	static int polyVal(Mat& coefficient, double x, double* val);
	/** @brief 求int型矩阵的众数
	
	@param input                  输入矩阵（int型）
	@param out                    输出结果
	@return 成功返回0，否则返回-1
	*/
	int get_mode_index(const Mat& input, int* out);
	/*计算矩阵梯度
	 参数1 源矩阵
	 参数2 行方向梯度（返回值）
	 参数3 列方向梯度（返回值）
	 参数4 是否补零使得梯度矩阵和源矩阵大小相同（默认补零）
	*/
	int diff(Mat& Src, Mat& diff_1, Mat& diff_2, bool same = true);
	/*计算干涉相位
	 参数1 主图像（复）
	 参数2 辅图像（复）
	 参数3 干涉相位（返回值）
	*/
	int generate_phase(const ComplexMat& Master, const ComplexMat& Slave, Mat& phase);

	/** @brief 最大似然相干估算器
	 
	@param master_image                       主图像（复）
	@param slave_image                        辅图像（复）
	@param coherence                          相干系数（返回值）
	@return 成功返回0，否则返回-1
	*/
	int real_coherence(ComplexMat& master_image, ComplexMat& slave_image, Mat& coherence);
	/** @brief 最大似然相干估算器（带估计窗口尺寸接口）
	
	@param master_image                       主图像（复）
	@param slave_image                        辅图像（复）
	@param est_wndsize_rg                     估计窗口距离向尺寸（奇数）
	@param est_wndsize_az                     估计窗口方位向尺寸（奇数）
	@param coherence                          相干系数（返回值）
	*/
	int real_coherence(
		const ComplexMat& master_image,
		const ComplexMat& slave_image,
		int est_wndsize_rg,
		int est_wndsize_az,
		Mat& coherence
	);
	/** @brief 频率无关相干估算器
	
	 @param master_image                        主图像（复）
	 @param slave_image                         辅图像（复）
	 @param coherence                           相干系数（返回值）
	 @return 成功返回0，否则返回-1
	*/
	int complex_coherence(ComplexMat& master_image, ComplexMat& slave_image, Mat& coherence);
	/** @brief 频率无关相干估算器（带估计窗口尺寸接口）
	
	@param master_image                         主图像
	@param slave_image                          辅图像
	@param est_wndsize_rg                       估计窗口距离向尺寸（奇数）
	@param est_wndsize_az                       估计窗口方位向尺寸（奇数）
	@param coherence                            相关系数（返回值）
	@return 成功返回0，否则返回-1
	*/
	int complex_coherence(
		const ComplexMat& master_image,
		const ComplexMat& slave_image,
		int est_wndsize_rg,
		int est_wndsize_az,
		Mat& coherence
	);
	/** @brief 根据干涉相位求相关系数
	@param phase                          输入相位
	@param coherence                      相关系数（返回值）
	@return 成功返回0，否则返回-1
	*/
	int phase_coherence(Mat& phase, Mat& coherence);
	/** @brief 根据干涉相位求相关系数（带估计窗口尺寸接口）
	
	@param phase                          输入相位
	@param est_wndsize_rg                 估计窗口距离向尺寸（奇数）
	@param est_wndsize_az                 估计窗口方位向尺寸（奇数）
	@param coherence                      相关系数（返回值）
	@return 成功返回0，否则返回-1
	*/
	int phase_coherence(
		const Mat& phase,
		int est_wndsize_rg,
		int est_wndsize_az,
		Mat& coherence
	);
	/*求解相位导数方差
	* 参数1 干涉相位
	* 参数2 相位导数方差（返回值）
	* 参数3 计算窗口大小（奇数）
	*/
	int phase_derivatives_variance(Mat& phase, Mat& phase_derivatives_variance, int wndsize = 3);
	/*FFTSHIFT
	 参数1 待fftshift的矩阵（原地进行fftshift操作）
	*/
	int fftshift(Mat& matrix);
	/*计算干涉相位图的残差值（点）
	 参数1 干涉相位
	 参数2 残差点矩阵（返回值）
	*/
	int residue(Mat& phase, Mat& residue);
	/*计算Delaunay三角网络的残差值（并且标注残差边和残差节点,便于解缠时避开）
	* 参数1 Delaunay三角网三角形结构体数组
	* 参数2 Delaunay三角网三角形数量
	* 参数3 Delaunay三角网节点数组
	* 参数4 Delaunay三角网边结构体数组
	* 参数5 Delaunay三角网边数量
	*/
	int residue(triangle* tri, int num_triangle, vector<tri_node>& nodes, tri_edge* edges, int num_edges);
	/** @brief 计算Delaunay三角网络的残差值（并且标注残差边和残差节点）
	@param triangle                              Delaunay三角网三角形结构体数组
	@param nodes                                 Delaunay三角网节点数组
	@param edges                                 Delaunay三角网边结构体数组
	@param distance_thresh                       边长度阈值（超过此阈值不参与残差点计算）
	@return 成功返回0，否则返回-1
	*/
	int residue(
		vector<triangle>& triangle,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges,
		double distance_thresh
	);
	/*计算mask（筛选高质量点）
	* 参数1 相关系数矩阵
	* 参数2 mask举矩阵（返回值）
	* 参数3 窗口半径
	* 参数4 阈值
	*/
	int gen_mask(Mat& coherence, Mat& mask, int wnd_size, double thresh);
	/*@brief 根据相位导数方差和设定阈值计算高质量掩膜
	* @param phase_derivatives_variance                   相位导数方差
	* @param mask                                         输出高质量掩膜
	* @param wndsize                                      计算掩膜窗口大小
	* @param thresh                                       阈值
	* @return 成功返回0，否则返回-1
	*/
	int gen_mask_pdv(
		Mat& phase_derivatives_variance,
		Mat& mask,
		int wndsize,
		double thresh
	);
	/*计算mask（筛选高质量点）
	* 参数1 相关系数矩阵
	* 参数2 相位导数方差
	* 参数3 mask举矩阵（返回值）
	* 参数4 窗口半径
	* 参数5 相关系数阈值
	* 参数6 相位导数方差阈值
	*/
	int gen_mask(
		Mat& coherence,
		Mat& phase_derivatives,
		Mat& mask, int wnd_size,
		double coh_thresh,
		double phase_derivative_thresh
	);
	/*根据设定阈值筛选残差点
	* 参数1 原始残差点矩阵
	* 参数2 筛选后残差点矩阵
	* 参数3 筛选阈值（大于0）
	* 参数4 残差点个数
	*/
	int residue_sift(Mat& residue_src, Mat& residue_dst, double thresh, long* num_residue);
	/*缠绕相位至（-pi,pi）
	 参数1 待缠绕相位
	 参数2 缠绕后的相位（返回值）
	*/
	int wrap(Mat& Src, Mat& Dst);

	/*按行或列累计积分
	 参数1 待积分数据
	 参数2 积分方向(dim = 1,按列计算 dim = 2,按行计算)
	*/
	int cumsum(Mat& phase, int dim);
	/*叉乘运算（三维）
	* 参数1 向量一(n * 3)
	* 参数2 向量二(n * 3)
	* 参数3 输出
	*/
	int cross(Mat& vec1, Mat& vec2, Mat& out);
	/*写入DIMACS文件（描述最小费用问题）
	 参数1 目标文件名
	 参数2 残差点矩阵
	 参数3 相干系数矩阵
	 参数4 残差点阈值(大于0)
	*/
	int write_DIMACS(const char* DIMACS_file_problem, Mat& residue, Mat& coherence, double thresh);
	/*@brief 写入DIMACS文件（表述改进的最小费用流问题）
	* @param DIMACS_problem_file      目标文件
	* @param residue                  残差点矩阵
	* @param mask                     可行路径区域掩膜(int型)
	* @param cost                     流费用
	* @param thresh                   残差点阈值（默认为0.7）
	* @return 成功返回0，否则返回-1
	*/
	int write_DIMACS(
		const char* DIMACS_problem_file,
		const Mat& residue,
		Mat& mask,
		const Mat& cost,
		double thresh = 0.7
	);
	/*写入DIMACS文件（描述最小费用问题，不规则三角网络）
	* 参数1 目标文件名
	* 参数2 Delaunay三角形结构体数组
	* 参数3 Delaunay三角形数量
	* 参数4 Delaunay三角网节点数组
	* 参数5 Delaunay三角网边结构体数组
	* 参数6 Delaunay三角网边数量
	* 参数7 每个节点的费用
	*/
	int write_DIMACS(
		const char* DIMACS_file_problem,
		triangle* tri,
		int num_triangle,
		vector<tri_node>& nodes,
		tri_edge* edges,
		long num_edges,
		Mat& cost
	);
	/** @brief 写入DIMACS文件（描述最小费用问题，Delaunay三角网络）
	
	@param DIMACS_file_problem                         目标DIMACS文件
	@param triange                                     Delaunay三角形结构体数组
	@param nodes                                       Delaunay三角网节点数组
	@param edges                                       Delaunay三角网边结构体数组
	@param cost                                        每个节点的费用
	@return 成功返回0，否则返回-1
	*/
	int write_DIMACS(
		const char* DIMACS_file_problem,
		vector<triangle>& triangle,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges,
		const Mat& cost
	);
	/*读取DIMACS文件（获取求解器求解结果）
	 参数1 最小费用流问题解文件
	 参数2 枝切路径1
	 参数3 枝切路径2
	 参数4 干涉相位图像行数
	 参数5 干涉相位图像列数
	*/
	int read_DIMACS(const char* DIMACS_file_solution, Mat& k1, Mat& k2, int rows, int cols);
	/*读取DIMACS文件（获取求解器求解结果）
	* 参数1 最小费用流问题解文件
	* 参数2 Delaunay三角网边结构体数组
	* 参数3 Delaunay三角网边数量
	* 参数4 Delaunay三角网节点数组
	* 参数5 Delaunay三角网三角形数组
	* 参数6 Delaunay三角网三角形数量
	*/
	int read_DIMACS(
		const char* DIMACS_file_solution,
		tri_edge* edges,
		int num_edges,
		vector<tri_node>& nodes,
		triangle* tri,
		int num_triangle
	);
	/** @brief 读取DIMACS文件（获取求解器求解结果）
	
	@param DIMACS_file_solution                         最小费用流问题解文件
	@param edges                                        Delaunay三角网边结构体数组
	@param nodes                                        Delaunay三角网节点数组
	@param triangle                                     Delaunay三角网三角形数组
	@param return 成功返回0，否则返回-1
	*/
	int read_DIMACS(
		const char* DIMACS_file_solution,
		vector<tri_edge>& edges,
		vector<tri_node>& nodes,
		vector<triangle>& triangle
	);
	/*将OpenCV Mat数据以二进制方式写入目标文件
	* 参数1 目标文件名
	* 参数2 待写入数据
	*/
	int cvmat2bin(const char* Dst_file, Mat& Src);
	/*从二进制文件中读数据，并将数据转换成OpenCV Mat格式
	* 参数1 二进制文件
	* 参数2 目标矩阵
	*/
	int bin2cvmat(const char* Src_file, Mat& Dst);
	/*InSAR多视处理（配准之后进行， 改变图像尺寸）
	* 参数1 主图像（SLC）
	* 参数2 辅图像（SLC）
	* 参数3 多视相位
	* 参数4 多视倍数（大于1）
	*/
	int multilook(ComplexMat& Master, ComplexMat& Slave, Mat& phase, int multilook_times);
	/** @brief InSAR多视处理（不改变图像尺寸）
	
	@param master_slc                    主图像
	@param slave_slc                     辅图像
	@param multilook_rg                  距离向多视倍数
	@param multilook_az                  方位向多视倍数
	@param multilooked_phase             多视相位
	*/
	int multilook(const ComplexMat& master, const ComplexMat& slave, int multilook_rg, int multilook_az, Mat& phase);
	/*@brief InSAR多视处理（改变窗口尺寸）
	* @param master                      主图像
	* @param slave                       复图像
	* @param multilook_rg                距离向多视倍数
	* @param multilook_az                方位向多视倍数
	* @param phase                       多视相位
	* @return 成功返回0，否则返回-1
	*/
	int Multilook(
		const ComplexMat& master, 
		const ComplexMat& slave, 
		int multilook_rg, 
		int multilook_az,
		Mat& phase
	);
	/*@brief 相位多视处理(改变尺寸)
	* @param phase                      待处理相位
	* @param outPhase                   处理结果
	* @param multi_rg                   距离向多视倍数
	* @param multi_az                   方位向多视倍数
	* @return 成功返回0，否则返回-1
	*/
	int multilook(
		const Mat& phase,
		Mat& outPhase,
		int multi_rg,
		int multi_az
	);
	/*@brief SAR图像多视
	* @param amplitude                 SAR图像幅度图
	* @param outAmplitude              多视SAR图像
	* @param multilook_rg              距离向多视倍数
	* @param multilook_az              方位向多视倍数
	* @return 成功返回0，否则返回-1
	*/
	int multilook_SAR(
		const Mat& amplitude,
		Mat& outAmplitude,
		int multilook_rg,
		int multilook_az
	);
	/** @brief 将相位转换成cos和sin（实部和虚部，支持double和float）
	
	@param phase                     输入相位
	@param cos                       实部
	@param sin                       虚部
	@return 成功返回0，否则返回-1
	*/
	int phase2cos(const Mat& phase, Mat& cos, Mat& sin);
	/*84坐标系转经纬高坐标系
	* 参数1 84坐标系坐标
	* 参数2 经纬高坐标系坐标（度/度/米）
	*/
	int xyz2ell(Mat xyz, Mat& llh);
	/*经纬高坐标系转84坐标系
	* 参数1 经纬高坐标系坐标（纬度/经度/高度）
	* 参数2 84坐标系坐标
	*/
	int ell2xyz(Mat llh, Mat& xyz);
	/*@brief 经/纬/高 ---> x/y/z
	* @param lon                 经度
	* @param lat                 纬度
	* @param elevation           高度
	* @param xyz                 x/y/z
	* @return 成功返回0，否则返回-1
	*/
	static int ell2xyz(double lon, double lat, double elevation, Position& xyz);



	/*******************************************************/
	/*                     图像存储工具集                  */
	/*******************************************************/

	/*量化保存SLC功率图
	* 参数1 目标文件名
	* 参数2 功率量化参数（可视范围dB）
	* 参数3 单视复图像
	*/
	int saveSLC(const char* filename, double db, ComplexMat& SLC);
	/*@brief SAR图像量化
	* @param filename       保存目标文件
	* @param db             量化动态范围
	* @param slc            单视复图像
	* @return 成功返回0，否则返回-1
	*/
	int SAR_image_quantify(const char* filename, double db, ComplexMat& SLC);
	/*@brief 量化保存SAR幅度图
	* @param filename             保存文件名
	* @param amplitude            幅度数据
	* @return 成功返回0，否则返回-1
	*/
	int saveAmplitude(
		const char* filename,
		Mat& amplitude
	);
	/*保存干涉相位图
	* 参数1 目标文件名
	* 参数2 颜色映射（jet/hsv/cool/parula等）
	* 参数3 待保存相位
	*/
	int savephase(const char* filename, const char* colormap, Mat phase);
	/*保存干涉相位图
	* 参数1 目标文件名
	* 参数2 颜色映射（jet/hsv/cool/parula等）
	* 参数3 待保存相位
	*/
	int save_coherence(const char* filename, const char* colormap, Mat coherence);
	/*@brief 保存干涉相位图（掩膜区域为黑色）
	* @param filename                            目标文件名
	* @param colormap                            颜色映射（jet/hsv/cool/parula等）
	* @param phase                               待保存相位
	* @param mask                                (int型)
	* @return 成功返回0，否则返回-1
	*/
	int savephase_black(const char* filename, const char* colormap, Mat& phase, Mat& mask);
	/*@brief 保存干涉相位图（掩膜区域为白色）
	* @param filename                            目标文件名
	* @param colormap                            颜色映射（jet/hsv/cool/parula等）
	* @param phase                               待保存相位
	* @param mask                                (int型)
	* @return 成功返回0，否则返回-1
	*/
	int savephase_white(const char* filename, const char* colormap, Mat& phase, Mat& mask);
	/*图像重采样
	* 参数1 原图像
	* 参数2 目标图像
	* 参数3 目标图像高度
	* 参数4 目标图像宽度
	*/
	int resampling(const char* Src_file, const char* Dst_file, int dst_height, int dst_width);
	/*量化SAR图像与干涉相位叠加
	* 参数1 量化SAR图像
	* 参数2 干涉相位图
	* 参数3 叠加图像
	* 参数4 SAR图像占比
	*/
	int amplitude_phase_blend(
		const char* amplitude_file,
		const char* phase_file,
		const char* blended_file,
		double SAR_ratio = 0.9
	);



	/*******************************************************/
	/*                Delaunay三角网相关函数库             */
	/*******************************************************/

	/*从.edge文件读取Delaunay三角网的边信息
	* 参数1 .edge文件
	* 参数2 指向边结构体的指针（返回值，内存需要手动释放）
	* 参数3 指向边个数的指针（返回值）
	* 参数4 统计每个节点的邻接边数（返回值，内存需要手动释放）
	* 参数5 节点数
	*/
	int read_edges(const char* filename, tri_edge** edges, long* num_edges, int** neighbours, long num_nodes);
	/** @brief 从.edge文件读取Delaunay三角网的边信息
	
	@param edge_file               .edge文件
	@param num_nodes               节点数
	@param edges                   Delaunay三角网边数组（返回值）
	@param node_neighbours         每个节点的邻接边数（返回值）
	@return  成功返回0， 否则返回-1
	*/
	int read_edges(
		const char* edge_file,
		vector<tri_edge>& edges,
		vector<int>& node_neighbours,
		long num_nodes
	);
	/*初始化Delaunay三角网节点
	* 参数1 节点数组（返回值）
	* 参数2 相位(double型)
	* 参数3 相位mask（int 型）
	* 参数4 edges结构体数组
	* 参数5 edges个数
	* 参数6 每个节点的邻接边信息
	* 参数7 节点数
	*/
	int init_tri_node(
		vector<tri_node>& node_array,
		Mat& phase,
		Mat& mask,
		tri_edge* edges,
		long num_edges,
		int* num_neighbour,
		int num_nodes
	);
	/** @brief 初始化Delaunay三角网节点
	
	@param node_array                 节点数组（返回值）
	@param phase                      相位值
	@param mask                       相位掩膜
	@param edges                      Delaunay三角网络边结构体数组
	@param node_neighbours            每个节点的邻边个数
	@param num_nodes                  节点数
	@return 成功返回0，否则返回-1
	*/
	int init_tri_node(
		vector<tri_node>& node_array,
		const Mat& phase,
		const Mat& mask,
		const vector<tri_edge>& edges,
		const vector<int>& node_neighbours,
		int num_nodes
	);
	/** @brief 初始化Delaunay三角网络边相位差
	
	@param edges                  Delaunay三角网络边数组（已经使用read_edges函数初始化过的）
	@param node_array             Delaunay三角网络节点数组（已经使用init_tri_node函数初始化过的）
	@return 成功返回0，否则返回-1
	*/
	int init_edge_phase_diff(
		vector<tri_edge>& edges,
		const vector<tri_node>& node_array
	);
	/*初始化Delaunay三角网边的相位质量
	* 参数1 相位质量图
	* 参数2 Delaunay三角网边结构体数组指针
	* 参数3 Delaunay三角网边结构体数组大小
	* 参数4 Delaunay三角网节点数组
	*/
	int init_edges_quality(Mat& quality, tri_edge* edges, int num_edges, vector<tri_node>& nodes);
	/** @brief 初始化Delaunay三角网边的相位质量指数
	
	@param quality_index                  相位质量图指数（与相位质量相反）
	@param edges                          Delaunay三角网边结构体数组
	@param nodes                          Delaunay三角网节点数组
	@return 成功返回0， 否则返回-1
	*/
	int init_edges_quality(
		const Mat& quality_index,
		vector<tri_edge>& edges,
		const vector<tri_node>& nodes
	);
	/*从.ele文件和.neigh文件读取Delaunay三角网的三角形信息
	* 参数1 .ele文件
	* 参数2 .neigh文件
	* 参数3 三角形结构体数组指针（返回值, 内存需要手动释放）
	* 参数4 三角形个数（返回值）
	* 参数5 Delaunay三角网节点数组
	* 参数6 Delaunay三角网边数组
	* 参数7 Delaunay三角网边数量
	*/
	int read_triangle(
		const char* ele_file,
		const char* neigh_file,
		triangle** tri,
		int* num_triangle,
		vector<tri_node>& nodes,
		tri_edge* edges,
		int num_edgs
	);
	/** @brief 从.ele文件和.neigh文件读取Delaunay三角网的三角形信息
	
	@param ele_file                        .ele文件
	@param neigh_file                      .neigh文件
	@param triangle                        三角形结构体数组（返回值）
	@param nodes                           Delaunay三角网节点数组
	@param edges                           Delaunay三角网边数组
	@return 成功返回0，否则返回-1
	*/
	int read_triangle(
		const char* ele_file,
		const char* neigh_file,
		vector<triangle>& triangle,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges
	);
	/*生成Delaunay三角网
	* 参数1 .node文件
	* 参数2 triangle.exe程序路径
	*/
	int gen_delaunay(const char* filename, const char* exe_path);
	/*写.node文件
	* 参数1 .node文件
	* 参数2 节点数组
	*/
	int write_node_file(const char* filename, const Mat& mask);




	/*********************************************************/
    /*                PS-InSAR 常用函数                      */
    /*********************************************************/

	/*振幅离差指数法筛选PS点（D_A）
	* 参数1 SAR幅度矩阵组
	* 参数2 振幅离差阈值
	* 参数3 mask（满足条件的PS点位置mask为1，其他为0）
	*/
	int PS_amp_dispersion(const vector<Mat>& amplitude, double thresh, Mat& mask);
	/*fifth-order butterworth filter（五阶巴特沃斯滤波器）
	* 参数1 grid_size
	* 参数2 n_win
	* 参数3 low_pass_wavelength
	* 参数4 滤波器系数（返回值）
	*/
	int butter_lowpass(int grid_size, int n_win, double low_pass_wavelength, Mat& lowpass);
	/*circle_shift
	*/
	int circshift(Mat& out, const cv::Point& delta);
	/*fftshift2
	*/
	int fftshift2(Mat& out);
	/*ifftshift
	*/
	int ifftshift(Mat& out);
	/*二维傅里叶变换
	* 参数1 输入矩阵
	* 参数2 输出结果
	*/
	int fft2(Mat& Src, Mat& Dst);
	/*复数二维傅里叶变换
	* 参数1 输入矩阵
	* 参数2 输出结果
	*/
	int fft2(ComplexMat& src, ComplexMat& dst);
	/*逆二维傅里叶变换
	* 参数1 输入矩阵
	* 参数2 输出结果
	*/
	int ifft2(ComplexMat& src, ComplexMat& dst);
	/*求标准差
	* 参数1 输入矩阵
	* 参数2 标准差返回值
	*/
	int std(const Mat& input, double* std);
	/*裁剪感兴趣的SAR图像区域（AOI）
	* 参数1 SAR图像序列文件名（img格式）
	* 参数2 裁剪后的SAR图像序列保存路径
	* 参数2 AOI中心纬度/经度/高度(1×3)
	* 参数3 AOI宽（列数）
	* 参数4 AOI高（行数）
	*/
	int PS_cut_AOI(
		vector<string>& SAR_images_files,
		const char* save_path,
		Mat& llh,
		int rows,
		int cols
	);
	/** @brief 时序SAR图像联合配准(所有slc同时载入内存)
	
	@param SAR_images            时序SAR图像（inplace，原地操作）
	@param offset                配准后左上角偏移量(尺寸：n_images × 2) 
	@param Master_index          主图像序号(序号从1开始)
	@param coh_method            采用实相关还是复相关（0代表实相关， 1代表复相关）
	@param interp_times          插值倍数（2的n次幂）
	@param blocksize             子块大小（2的n次幂）
	*/
	int stack_coregistration(
		vector<ComplexMat>& SAR_images,
		Mat& offset,
		int Master_index,
		int coh_method,
		int interp_times,
		int blocksize
	);
	/** @brief 时序SAR图像联合配准(slc串行载入内存，以节省内存)
	
	@param SAR_images            时序SAR图像文件
	@param SAR_images_out        配准结果文件
	@param offset                配准后左上角偏移量(尺寸：n_images × 2)
	@param Master_index          主图像序号(序号从1开始)
	@param interp_times          插值倍数（2的n次幂）
	@param blocksize             子块大小（2的n次幂）
	*/
	int stack_coregistration(
		vector<string>& SAR_images,
		vector<string>& SAR_images_out,
		Mat& offset,
		int Master_index,
		int interp_times,
		int blocksize
	);
	/** @brief 时序SAR图像联合配准（串行、分块配准，支持16位整型和64位浮点型输入）
	* 
	* @param SAR_images                     时序SAR图像文件
	* @param SAR_images_out                 配准结果文件
	* @param Master_index                   主图像序号（从1开始）
	* @param interp_times                   插值倍数（2的n次幂）
	* @param blocksize                      子块大小（2的n次幂）
	* @return 成功返回0，否则返回-1
	*/
	int stack_coregistration(
		vector<string>& SAR_images,
		vector<string>& SAR_images_out,
		int Master_index,
		int interp_times,
		int blocksize
	);
	/*hist函数（统计直方图函数）
	* 参数1 待统计数据
	* 参数2 统计标准下限区间中心
	* 参数3 统计标准上限区间中心
	* 参数4 区间半径（n * 区间半径 = （统计标准上限区间中心 - 统计标准下限区间中心））
	* 参数5 统计输出
	*/
	int hist(
		Mat& input,
		double lowercenter,
		double uppercenter,
		double interval,
		Mat& out
	);
	/*@brief 直方图统计函数
	* @param input                   输入待统计数据
	* @param lowerbound              区间下界
	* @param upperbound              区间上界
	* @param interval                统计区间间隔
	* @param out_x                   输出结果（横坐标）
	* @param out_y                   输出结果（纵坐标）
	* @return 成功返回0，否则返回-1
	*/
	int hist(
		Mat& input,
		double lowerbound,
		double upperbound,
		double interval,
		Mat& out_x,
		Mat& out_y
	);
	/*@brief 高斯曲线拟合
	* @param input_x                输入横坐标
	* @param input_y                输入纵坐标
	* @param mu                     均值
	* @param sigma_square           方差
	* @param scale                  幅度
	* @return 成功返回0，否则返回-1
	*/
	int gaussian_curve_fit(
		Mat& input_x,
		Mat& input_y,
		double* mu,
		double* sigma_square,
		double* scale
	);
	/*
	* 卫星轨道插值
	* 参数1：卫星轨道参数（未插值）
	* 参数2：插值时间间隔（s）
	* 参数3：插值结果
	*/
	int stateVec_interp(Mat& stateVec, double time_interval, Mat& stateVec_interp);
	/*
	* 从h5（SLC）图像文件中裁剪AOI
	* 参数1：h5文件
	* 参数2：AOI左上角经度
	* 参数3：AOI左上角纬度
	* 参数4：AOI右下角经度
	* 参数5：AOI右下角纬度
	* 参数6：输出单视复图像
	* 参数7：AOI左上角行偏移量（从0开始，0代表不偏移）
	* 参数8：AOI左上角列偏移量（从0开始，0代表不偏移）
	*/
	int get_AOI_from_h5SLC(
		const char* h5_file,
		double lon_topleft,
		double lat_topleft,
		double lon_bottomright,
		double lat_bottomright,
		ComplexMat& slc,
		int* offset_row = NULL,
		int* offset_col = NULL
	);
	/** @brief 从h5（SLC）文件中裁剪出AOI区域
	
	@param h5_file h5文件
	@param lon_center AOI中心经度
	@param lat_center AOI中心纬度
	@param width AOI宽度（m）
	@param height AOI高度（m）
	@param slc 裁剪结果slc
	@param offset_row AOI左上角在原图像中行偏移量（从0开始，0代表不偏移）
	@param offset_col AOI左上角在原图像中行偏移量（从0开始，0代表不偏移）
	*/
	int get_AOI_from_h5slc(
		const char* h5_file,
		double lon_center,
		double lat_center,
		double width,
		double height,
		ComplexMat& slc,
		int* offset_row = NULL,
		int* offset_col = NULL
	);
	/** @brief 从h5（SLC）文件中获取裁剪AOI区域的尺寸

	@param h5_file          h5文件
	@param lon_center       AOI中心经度
	@param lat_center       AOI中心纬度
	@param width            AOI宽度（m）
	@param height           AOI高度（m）
	@param AOI_rows         AOI行数
	@param AOI_cols         AOI列数
	@param offset_row       AOI左上角在原图像中行偏移量（从0开始，0代表不偏移）
	@param offset_col       AOI左上角在原图像中行偏移量（从0开始，0代表不偏移）
	*/
	int get_AOI_size(
		const char* h5_file,
		double lon_center,
		double lat_center,
		double width,
		double height,
		int* AOI_rows,
		int* AOI_cols,
		int* offset_row = NULL,
		int* offset_col = NULL
	);
	/** @brief 坐标转换工具函数
	
	@param coefficient       转换系数矩阵
	@param coord_in_1        原坐标矩阵1(1和2的顺序很重要，经度/行坐标在前)
	@param coord_in_2        原坐标矩阵2
	@param coord_out         转换结果矩阵
	*/
	int coord_conversion(
		Mat& coefficient,
		Mat& coord_in_1,
		Mat& coord_in_2,
		Mat& coord_out
	);
	/** @brief 基线估计

	@param stateVec1               主星轨道（未插值）
	@param stateVec2               辅星轨道（未插值）
	@param lon_coef                主星坐标转换系数（图像坐标-->经度）
	@param lat_coef                主星坐标转换系数（图像坐标-->纬度）
	@param offset_row              主图像左上角在原始图像中的行偏移量
	@param offset_col              主图像左上角在原始图像中的列偏移量
	@param scene_height            场景高度(像素行数)
	@param scene_width             场景宽度(像素列数)
	@param interp_interval1        主星轨道插值时间间隔（1/prf）
	@param interp_interval2        辅星轨道插值时间间隔（1/prf）
	@param B_effect                垂直基线长度（返回值）
	@param B_parallel              平行基线长度（返回值）
	@param sigma_B_effect          垂直基线估计标准差（返回值）
	@param sigma_B_parallel        平行基线估计标准差（返回值）
	*/
	int baseline_estimation(
		const Mat& stateVec1,
		const Mat& stateVec2,
		const Mat& lon_coef,
		const Mat& lat_coef,
		int offset_row,
		int offset_col,
		int scene_height,
		int scene_width,
		double interp_interval1,
		double interp_interval2,
		double* B_effect,
		double* B_parallel,
		double* sigma_B_effect = NULL,
		double* sigma_B_parallel = NULL
	);
	/** @brief 基线估计

	@param stateVec1               主星轨道（未插值）
	@param stateVec2               辅星轨道（未插值）
	@param lon_center              主图像场景中心坐标（经度）
	@param lat_center              主图像场景中心坐标（维度）
	@param offset_row              主图像左上角在原始图像中的行偏移量
	@param offset_col              主图像左上角在原始图像中的列偏移量
	@param scene_height            场景高度(像素行数)
	@param scene_width             场景宽度(像素列数)
	@param interp_interval1        主星轨道插值时间间隔（1/prf）
	@param interp_interval2        辅星轨道插值时间间隔（1/prf）
	@param B_effect                垂直基线长度（返回值）
	@param B_parallel              平行基线长度（返回值）
	*/
	int baseline_estimation(
		const Mat& stateVec1,
		const Mat& stateVec2,
		double lon_center,
		double lat_center,
		int offset_row,
		int offset_col,
		int scene_height,
		int scene_width,
		double interp_interval1,
		double interp_interval2,
		double* B_effect,
		double* B_parallel
	);
	/** @brief 基线估计

	@param stateVec1               主星轨道（未插值）
	@param stateVec2               辅星轨道（未插值）
	@param lon_center              主图像场景中心坐标（经度）
	@param lat_center              主图像场景中心坐标（维度）
	@param dem_center              主图像场景中心坐标（高度）
	@param offset_row              主图像左上角在原始图像中的行偏移量
	@param offset_col              主图像左上角在原始图像中的列偏移量
	@param scene_height            场景高度(像素行数)
	@param scene_width             场景宽度(像素列数)
	@param interp_interval1        主星轨道插值时间间隔（1/prf）
	@param interp_interval2        辅星轨道插值时间间隔（1/prf）
	@param B_effect                垂直基线长度（返回值）
	@param B_parallel              平行基线长度（返回值）
	*/
	int baseline_estimation(
		const Mat& stateVec1,
		const Mat& stateVec2,
		double lon_center,
		double lat_center,
		double dem_center,
		int offset_row,
		int offset_col,
		int scene_height,
		int scene_width,
		double interp_interval1,
		double interp_interval2,
		double* B_effect,
		double* B_parallel
	);
	/*@brief 相关矩阵法同质检验 + phase linking
	* @param slc_stack                           待处理SLC数据堆栈（支持32位float型数据类型）
	* @param slc_stack_filtered                  phase-linking后的结果（返回值）
	* @param test_wndsize                        同质检验搜索窗口大小（奇数，默认为15）
	* @param est_wndsize                         相关矩阵估计窗口大小（奇数，默认为3）
	* @return 成功返回0，否则返回-1
	*/
	int homogeneous_selection_and_phase_linking(
		vector<ComplexMat>& slc_stack,
		vector<ComplexMat>& slc_stack_filtered,
		int test_wndsize = 15,
		int est_wndsize = 3
	);
	/*@brief Sum of Kronecker decomposition（SKP分解）
	* @param inputMat                            待分解矩阵
	* @param nr1                                 分解参数1
	* @param nc1                                 分解参数2
	* @param nr2                                 分解参数3
	* @param nc2                                 分解参数4
	* @param outputMat                           分解后矩阵（返回值）
	* @return 成功返回0，否则返回-1
	*/
	int SKP_decomposition(
		ComplexMat& inputMat,
		int nr1,
		int nc1, 
		int nr2,
		int nc2,
		vector<ComplexMat>& outputMat1,
		vector<ComplexMat>& outputMat2
	);
	/** @brief 统计同质检验
	
	@param pixel1            待检验像元1幅度序列(size: n_images×1)
	@param pixel2            待检验像元2幅度序列(size: n_images×1)
	@param homo_flag         是否为同质像元(返回0则为同质像元，-1则为非同质像元)
	@param alpha             显著性水平（可以设定的值为 0.20,0.15,0.10,0.05,0.025,0.01,0.005,0.001。默认为0.05）
	@param method            检验方法（"KS":Kolmogorov-Smirnov检验，"AD":Anderson-Darling检验, 默认为KS检验）
	@return                  正常运行返回0，报错返回-1
	*/
	int homogeneous_test(
		const Mat& pixel1,
		const Mat& pixel2,
		int* homo_flag,
		double alpha = 0.05,
		const char* method = "KS"
	);
	/*@brief 统计同质检验
	* @param slc_series      待处理SLC数据堆栈
	* @param windsize_az     窗口大小（方位向）
	* @param windsize_rg     窗口大小（距离向）
	* @param homo_num        各点的同质点个数（int型矩阵）
	* @param homo_index      各点同质点mask矩阵(uint8型矩阵,矩阵大小为（nr×nc）×（windsize_az×windsize_rg）)
	* @param alpha           显著性水平（可以设定的值为 0.20,0.15,0.10,0.05,0.025,0.01,0.005,0.001。默认为0.05）
	* @param method          检验方法（"KS":Kolmogorov-Smirnov检验，"AD":Anderson-Darling检验, 默认为KS检验）
	* @return 成功返回0，否则返回-1
	*/
	int homogeneous_test(
		const vector<ComplexMat>& slc_series,
		int windsize_az,
		int windsize_rg,
		Mat& homo_num,
		Mat& homo_index,
		double alpha = 0.05,
		const char* method = "KS"
	);
	/** @brief Hermitian矩阵特征值分解
	
	@param input               输入复矩阵（n×n, double型）
	@param eigenvalue          特征值（n×1实矩阵,从大到小排列）
	@param eigenvector         特征向量（n×n复矩阵， 列向量为特征向量）
	@return                    成功返回0，否则返回-1              
	*/
	int HermitianEVD(
		const ComplexMat& input,
		Mat& eigenvalue,
		ComplexMat& eigenvector
	);
	/** @brief 时序SAR图像复相关矩阵估计
	
	@param slc_series               slc数据堆栈
	@param coherence_matrix         相关矩阵（复数, 返回值）
	@param est_window_width         估计窗口宽度（奇数）
	@param est_window_height        估计窗口高度（奇数）
	@param ref_row                  （若进行统计同质检验）参考点行坐标，不进行同质检验则不需要此参数
	@param ref_col                  （若进行统计同质检验）参考点列坐标，不进行同质检验则不需要此参数
	@param b_homogeneous_test       是否进行统计同质检验（同质检验参考像素默认为中间点像素）
	@param b_normalize              估计相关矩阵时slc序列是否归一化处理
	@return                         成功返回0，否则返回-1 
	*/
	int coherence_matrix_estimation(
		const vector<ComplexMat>& slc_series,
		ComplexMat& coherence_matrix,
		int est_window_width,
		int est_window_height,
		int ref_row,
		int ref_col,
		bool b_homogeneous_test = true,
		bool b_normalize = true
	);
	/** @brief 多基线时间序列相位估计（分块读取、计算、储存）
	
	@param coregis_slc_files              配准后SAR图像数据堆栈（文件）
	@param phase_files                    时间序列干涉相位（文件，与coregis_slc_files数量相同，主图像相位为0）
	@param coherence_files                各辅图像与主图像之间的相关系数文件（是否估计相关系数取决于输入参数b_coh_est）
	@param master_indx                    主图像序号（从1开始）
	@param blocksize_row                  子块尺寸（行，必须大于同质检验搜索窗口半径）
	@param blocksize_col                  子块尺寸（列，必须大于同质检验搜索窗口半径）
	@param out_mask                       掩膜输出（标记经过EVD法估计的像素点，与参数thresh_c1_to_c2有关）
	@param b_coh_est                      是否估计相关系数（默认是）
	@param homogeneous_test_wnd           同质检验搜索窗口大小（奇数，homogeneous_test_wnd×homogeneous_test_wnd， 默认为21×21）
	@param thresh_c1_to_c2                协方差矩阵第2特征值与第1特征值比值阈值（0-1之间，默认为0.7）
	@param b_flat                         是否去平地相位（默认是）
	@param b_normalize                    协方差矩阵是否归一化（默认是）
	*/
	int MB_phase_estimation(
		vector<string> coregis_slc_files,
		vector<string> phase_files,
		vector<string> coherence_files,
		int master_indx,
		int blocksize_row,
		int blocksize_col,
		Mat& out_mask,
		bool b_coh_est = true,
		int homogeneous_test_wnd = 21,
		double thresh_c1_to_c2 = 0.7,
		bool b_flat = true,
		bool b_normalize = true
	);
	/*@brief SAR图像堆栈时空基线分布计算
	* @param SLCH5Files                SAR图像数据文件
	* @param reference                 参考图像序号
	* @param temporal                  时间基线（返回值,1×n，单位：day）
	* @param spatial                   空间基线（返回值,1×n，单位：m）
	* @return 成功返回0，否则返回-1
	*/
	int spatialTemporalBaselineEstimation(
		vector<string>& SLCH5Files,
		int reference,
		Mat& temporal,
		Mat& spatial
	);
	/** @brief 区域生长法解缠（delaunay三角网）
	
	@param nodes                       Delaunay三角网络节点数组
	@param edges                       Delaunay三角网络边结构体数组
	@param start_edge                  积分起始边序号（从1开始）
	@param distance_thresh             边长阈值，超过此阈值不通过此边积分
	@param quality_thresh              质量阈值，低于此阈值不通过此边积分
	@return 成功返回0，否则返回-1
	*/
	int unwrap_region_growing(
		vector<tri_node>& nodes,
		const vector<tri_edge>& edges,
		size_t start_edge,
		double distance_thresh,
		double quality_thresh
	);
	/*@brief 根据图像的大小、行列偏移以及行列-->经纬度的转换系数，计算图像的地理边界（最大最小经纬度）
	* @param lat_coefficient                        地理坐标转换系数（行列-->纬度）
	* @param lon_coefficient                        地理坐标转换系数（行列-->经度）
	* @param sceneHeight                            场景高度
	* @param sceneWidth                             场景宽度
	* @param offset_row                             场景在原图像中的行偏移量
	* @param offset_col                             场景在原图像中的列偏移量
	* @param lonMax                                 最大经度（返回值）
	* @param latMax                                 最大纬度（返回值）
	* @param lonMin                                 最小经度（返回值）
	* @param latMin                                 最小纬度（返回值）
	* @return 成功返回0，否则返回-1
	*/
	static int computeImageGeoBoundry(
		Mat& lat_coefficient,
		Mat& lon_coefficient,
		int sceneHeight,
		int sceneWidth,
		int offset_row,
		int offset_col,
		double* lonMax,
		double* latMax,
		double* lonMin,
		double* latMin
	);
	/*@brief 根据图像四角点经纬度，计算图像的地理边界（最大最小经纬度）
	@param topleft_lon                             左上角经度
	@param topleft_lat                             左上角纬度
	@param topright_lon                            右上角经度
	@param topright_lat                            右上角纬度
	@param bottomleft_lon                          左下角经度
	@param bottomleft_lat                          左下角纬度
	@param bottomright_lon                         右下角经度
	@param bottomright_lat                         右下角纬度
	@param lonMax                                  最大经度（返回值）
	@param latMax                                  最大纬度（返回值）
	@param lonMin                                  最小经度（返回值）
	@param latMin                                  最小纬度（返回值）
	@return 成功返回0，否则返回-1
	*/
	static int computeImageGeoBoundry(
		double topleft_lon,
		double topleft_lat,
		double topright_lon,
		double topright_lat,
		double bottomleft_lon,
		double bottomleft_lat,
		double bottomright_lon,
		double bottomright_lat,
		double* lonMax,
		double* latMax,
		double* lonMin,
		double* latMin
	);
	/*@brief 根据地理边界信息获取SRTM高程
	* @param filepath                     下载的SRTM高程文件保存路径
	* @param DEM_out                      DEM数据（返回值，short型）
	* @param lonUpperLeft                 左上角经度（返回值）
	* @param latUpperLeft                 左上角纬度（返回值）
	* @param lonMin                       最小经度
	* @param lonMax                       最大经度
	* @param latMin                       最小纬度
	* @param latMax                       最大纬度
	* @return 成功返回0，否则返回-1
	*/
	static int getSRTMDEM(
		const char* filepath,
		Mat& DEM_out,
		double* lonUpperLeft,
		double* latUpperLeft,
		double lonMin,
		double lonMax,
		double latMin,
		double latMax
	);
	/*@brief 根据地理边界信息计算所需下载的SRTM高程文件名
	* @param lonMin                       最小经度
	* @param lonMax                       最大经度
	* @param latMin                       最小纬度
	* @param latMax                       最大纬度
	* @param name                         文件名
	* @return 成功返回0，否则返回-1
	*/
	static int getSRTMFileName(
		double lonMin,
		double lonMax,
		double latMin,
		double latMax,
		vector<string>& name
	);
	/*@brief 下载SRTM高程数据
	* @param name                         文件名
	* @param DEMpath                      下载DEM文件保存路径
	* @return 成功返回0，否则返回-1
	*/
	static int downloadSRTM(const char* name, const char* DEMpath);
	/*@brief 根据四个角经纬度坐标，将图片叠加到Google Earth上
	* @param BottomLeft_lon                左下角经度
	* @param BottomLeft_lat                左下角纬度
	* @param BottomRight_lon               右下角经度
	* @param BottomRight_lat               右下角纬度
	* @param TopRight_lon                  右上角经度
	* @param TopRight_lat                  右上角纬度
	* @param TopLeft_lon                   左上角经度
	* @param TopLeft_lat                   左上角纬度
	* @param Reference_lon                 参考点经度
	* @param Reference_lat                 参考点纬度
	* @param image_file                    图像文件（必须与待写入的KML文件处在同一目录下）
	* @param KML_file                      待写入KML文件名
	* @param Legend_file                   图例文件（必须与待写入的KML文件处在同一目录下）
	* @return 成功返回0，否则返回-1
	*/
	static int writeOverlayKML(
		double BottomLeft_lon,
		double BottomLeft_lat,
		double BottomRight_lon,
		double BottomRight_lat,
		double TopRight_lon,
		double TopRight_lat,
		double TopLeft_lon,
		double TopLeft_lat,
		double Reference_lon,
		double Reference_lat,
		const char* image_file,
		const char* KML_file,
		const char* Legend_file = NULL
	);
	/*@brief 拼接哨兵一号3个子带干涉相位
	* @param IW1_h5file                     子带1干涉相位h5文件
	* @param IW2_h5file                     子带2干涉相位h5文件
	* @param IW3_h5file                     子带3干涉相位h5文件
	* @param merged_phase_h5file            拼接后干涉相位h5文件（覆盖写入）
	* @return 成功返回0，否则返回-1
	*/
	int S1_subswath_merge(
		const char* IW1_h5file,
		const char* IW2_h5file,
		const char* IW3_h5file,
		const char* merged_phase_h5file
	);
	/*@brief 拼接哨兵一号3个子带单视复图像
	* @param IW1_h5file                     子带1单视复图像h5文件
	* @param IW2_h5file                     子带2单视复图像h5文件
	* @param IW3_h5file                     子带3单视复图像h5文件
	* @param merged_slc_h5file            拼接后单视复图像h5文件（覆盖写入）
	* @return 成功返回0，否则返回-1
	*/
	int S1_subswath_merge_slc(
		const char* IW1_h5file,
		const char* IW2_h5file,
		const char* IW3_h5file,
		const char* merged_slc_h5file
	);
	/*@brief 拼接哨兵一号同一轨道相邻frame的干涉相位
	* @param h5files                        同一子带不同frame干涉相位h5数据文件
	* @param merged_phase_h5                拼接后的干涉相位h5文件
	* @return 成功返回0，否则返回-1
	*/
	int S1_frame_merge(
		vector<string>& h5files,
		const char* merged_phase_h5
	);
	/*@brief 拼接同一轨道相邻frame的单视复图像
	* @param frame1_h5                         待拼接frame1的h5文件
	* @param frame2_h5                         待拼接frame2的h5文件
	* @param outframe_h5                       拼接frame的h5文件（覆盖写入）
	* @return 成功返回0，否则返回-1
	*/
	int S1_frame_merge(
		const char* frame1_h5,
		const char* frame2_h5,
		const char* outframe_h5
	);
	/*@brief 相位地理编码：SAR图像坐标系--->墨卡托坐标系
	* @param mapped_lon                        相位对应的经度
	* @param mapped_lat                        相位对应的纬度
	* @param phase                             SAR图像坐标相位
	* @param mapped_phase                      墨卡托坐标相位（返回值）
	* @param interpolation_method              插值方法（0：最临近插值，1：双线性插值。默认为最临近插值）
	* @param lon_east                          编码图像最东边缘经度（返回值）
	* @param lon_west                          编码图像最西边缘经度（返回值）
	* @param lat_north                         编码图像最北边缘纬度（返回值）
	* @param lat_south                         编码图像最南边缘纬度（返回值）
	* @return 成功返回0，否则返回-1
	*/
	int SAR2UTM(
		Mat& mapped_lon,
		Mat& mapped_lat,
		Mat& phase,
		Mat& mapped_phase,
		int interpolation_method = 0,
		double* lon_east = NULL,
		double* lon_west = NULL,
		double* lat_north = NULL,
		double* lat_south = NULL
	);
	/*@brief 相位地理编码：SAR图像坐标系--->墨卡托坐标系
	* @param mapped_lon                        相位对应的经度
	* @param mapped_lat                        相位对应的纬度
	* @param phase                             SAR图像坐标相位
	* @param mapped_phase                      墨卡托坐标相位（返回值）
	* @param grid_size                         网格间距（m）
	* @param interpolation_method              插值方法（0：最临近插值，1：双线性插值。默认为最临近插值）
	* @param lon_east                          编码图像最东边缘经度（返回值）
	* @param lon_west                          编码图像最西边缘经度（返回值）
	* @param lat_north                         编码图像最北边缘纬度（返回值）
	* @param lat_south                         编码图像最南边缘纬度（返回值）
	* @return 成功返回0，否则返回-1
	*/
	int SAR2UTM(
		Mat& mapped_lon,
		Mat& mapped_lat,
		Mat& phase,
		Mat& mapped_phase,
		double grid_size,
		int interpolation_method = 0,
		double* lon_east = NULL,
		double* lon_west = NULL,
		double* lat_north = NULL,
		double* lat_south = NULL
	);
	/*@brief SLC复图像地理编码：SAR图像坐标系--->墨卡托坐标系
	* @param mapped_lon                        SLC对应的经度
	* @param mapped_lat                        SLC对应的纬度
	* @param slc                               SAR图像坐标SLC
	* @param mapped_slc                        墨卡托坐标SLC（返回值）
	* @param interpolation_method              插值方法（0：最临近插值，1：双线性插值。默认为最临近插值）
	* @param lon_east                          编码图像最东边缘经度（返回值）
	* @param lon_west                          编码图像最西边缘经度（返回值）
	* @param lat_north                         编码图像最北边缘纬度（返回值）
	* @param lat_south                         编码图像最南边缘纬度（返回值）
	* @return 成功返回0，否则返回-1
	*/
	int SAR2UTM(
		Mat& mapped_lon,
		Mat& mapped_lat,
		ComplexMat& slc,
		ComplexMat& mapped_slc,
		int interpolation_method = 0,
		double* lon_east = NULL,
		double* lon_west = NULL,
		double* lat_north = NULL,
		double* lat_south = NULL
	);

	/*@brief 干涉产品地理编码：SAR图像坐标系--->墨卡托坐标系
	* @param DEM84                        84坐标系DEM（short型矩阵）
	* @param input                        待编码产品
	* @param mapped_resolution_x          编码后产品东西向分辨率（m）
	* @param mapped_resolution_y          编码后产品南北向分辨率（m）
	* @param mapped_result                地理编码结果（返回值）
	* @param lon_upperleft                84坐标系DEM左上角经度
	* @param lat_upperleft                84坐标系DEM左上角纬度
	* @param offset_row                   SAR图像在原场景中的行偏移量
	* @param offset_col                   SAR图像在原场景中的列偏移量
	* @param sceneHeight                  SAR图像场景高度
	* @param sceneWidth                   SAR图像场景宽度
	* @param prf                          SAR卫星雷达脉冲重复频率
	* @param rangeSpacing                 距离向采样间隔（m）
	* @param wavelength                   波长
	* @param nearRangeTime                最近斜距时间
	* @param acquisitionStartTime         方位向采样开始时间
	* @param acquisitionStopTime          方位向采样结束时间
	* @param stateVector                  卫星轨道数据（未插值）
	* @param lon_spacing                  84坐标系DEM经度采样间隔（°）
	* @param lat_spacing                  84坐标系DEM纬度采样间隔（°）
	* @param lon_east                     编码图像最东边缘经度（返回值）
	* @param lon_west                     编码图像最西边缘经度（返回值）
	* @param lat_north                    编码图像最北边缘纬度（返回值）
	* @param lat_south                    编码图像最南边缘纬度（返回值）
	* @return 成功返回0，否则返回-1
	*/
	int geocode(
		Mat& DEM84,
		Mat& input,
		double mapped_resolution_x,
		double mapped_resolution_y,
		Mat& mapped_result,
		double lon_upperleft,
		double lat_upperleft,
		int offset_row,
		int offset_col,
		int sceneHeight,
		int sceneWidth,
		double prf,
		double rangeSpacing,
		double wavelength,
		double nearRangeTime,
		double acquisitionStartTime,
		double acquisitionStopTime,
		Mat& stateVector,
		double lon_spacing,
		double lat_spacing,
		double* lon_east = NULL,
		double* lon_west = NULL,
		double* lat_north = NULL,
		double* lat_south = NULL
	);

	/*@brief 单视复图像地理编码：SAR图像坐标系--->墨卡托坐标系
	* @param DEM84                        84坐标系DEM（short型矩阵）
	* @param slc                          待编码单视复图像
	* @param mapped_resolution_x          编码后产品东西向分辨率（m）
	* @param mapped_resolution_y          编码后产品南北向分辨率（m）
	* @param mapped_slc                   地理编码结果（返回值）
	* @param lon_upperleft                84坐标系DEM左上角经度
	* @param lat_upperleft                84坐标系DEM左上角纬度
	* @param offset_row                   SAR图像在原场景中的行偏移量
	* @param offset_col                   SAR图像在原场景中的列偏移量
	* @param sceneHeight                  SAR图像场景高度
	* @param sceneWidth                   SAR图像场景宽度
	* @param prf                          SAR卫星雷达脉冲重复频率
	* @param rangeSpacing                 距离向采样间隔（m）
	* @param wavelength                   波长
	* @param nearRangeTime                最近斜距时间
	* @param acquisitionStartTime         方位向采样开始时间
	* @param acquisitionStopTime          方位向采样结束时间
	* @param stateVector                  卫星轨道数据（未插值）
	* @param lon_spacing                  84坐标系DEM经度采样间隔（°）
	* @param lat_spacing                  84坐标系DEM纬度采样间隔（°）
	* @param interp_times                 84坐标系DEM插值倍数（默认值为10）
	* @param lon_east                     编码图像最东边缘经度（返回值）
	* @param lon_west                     编码图像最西边缘经度（返回值）
	* @param lat_north                    编码图像最北边缘纬度（返回值）
	* @param lat_south                    编码图像最南边缘纬度（返回值）
	* @return 成功返回0，否则返回-1
	*/
	int geocode(
		Mat& DEM84,
		ComplexMat& slc,
		double mapped_resolution_x,
		double mapped_resolution_y,
		ComplexMat& mapped_slc,
		double lon_upperleft,
		double lat_upperleft,
		int offset_row,
		int offset_col,
		int sceneHeight,
		int sceneWidth,
		double prf,
		double rangeSpacing,
		double wavelength,
		double nearRangeTime,
		double acquisitionStartTime,
		double acquisitionStopTime,
		Mat& stateVector,
		double lon_spacing,
		double lat_spacing,
		double* lon_east = NULL,
		double* lon_west = NULL,
		double* lat_north = NULL,
		double* lat_south = NULL
	);
	/*
	* @brief 利用地理配准网格文件（TropiSAR的.grille文件）将横向墨卡托投影的DTM和DSM投影至SAR坐标系
	* @param grille_file                       grille网格文件
	* @param DTM                               待投影的DTM或者DSM数据
	* @param xllcorner                         DTM左上角UTM_x坐标
	* @param yllcorner                         DTM左上角UTM_y坐标
	* @param prior_DTM                         SAR坐标系先验DTM
	* @param mapped_DTM                        投影至SAR坐标系的DTM
	* @param SAR_extent_x                      SAR场景x坐标范围(0~SAR_extent_x)
	* @param SAR_extent_y                      SAR场景y坐标范围(0~SAR_extent_y)
	* @return 成功返回0，否则返回-1
	*/
	int geo_transformation(
		const char* grille_file,
		Mat DTM,
		double xllcorner,
		double yllcorner,
		Mat& prior_DTM,
		Mat& mapped_DTM,
		int SAR_extent_x,
		int SAR_extent_y
	);
	/*
	* @brief 利用地理配准网格文件（TropiSAR的.grille文件）将WGS84坐标系（经纬高）的DTM和DSM投影至SAR坐标系
	* @param grille_file                       grille网格文件
	* @param DTM                               待投影的DTM或者DSM数据
	* @param lon_upleft                        DTM左上角经度
	* @param lat_upleft                        DTM左上角纬度
	* @param lon_interval                      经度采样间隔
	* @param lat_interval                      纬度采样间隔
	* @param prior_DTM                         SAR坐标系先验DTM
	* @param mapped_DTM                        投影至SAR坐标系的DTM
	* @param SAR_extent_x                      SAR场景x坐标范围(0~SAR_extent_x)
	* @param SAR_extent_y                      SAR场景y坐标范围(0~SAR_extent_y)
	* @return 成功返回0，否则返回-1
	*/
	int geo_transformation(
		const char* grille_file,
		Mat DTM,
		double lon_upleft,
		double lat_upleft,
		double lon_interval,
		double lat_interval,
		Mat& prior_DTM,
		Mat& mapped_DTM,
		int SAR_extent_x,
		int SAR_extent_y
	);
	/*
	* @brief 读取TropiSAR的.grille文件
	* @param grille_file                       待读取的grille网格文件
	* @param row_matrix                        每层网格的行信息
	* @param col_matrix                        每层网格的列信息
	* @param lon_matrix                        每层网格的经度信息
	* @param lat_matrix                        每层网格的纬度信息
	* @param height_vector                     每层网格的高度信息
	* @return 成功返回0，否则返回-1
	*/
	int read_grille(
		const char* grille_file,
		Mat& row_matrix,
		Mat& col_matrix,
		vector<Mat>& lon_matrix,
		vector<Mat>& lat_matrix,
		vector<double>& height_vector
	);
	/*
	* @brief 将经纬度坐标转换为UTM坐标
	* @param lon                                经度
	* @param lat                                纬度
	* @param UTM_X                              UTM X坐标
	* @param UTM_Y                              UTM Y坐标
	* @return 成功返回0，否则返回-1
	*/
	int lonlat2utm(
		Mat lon,
		Mat lat,
		Mat& UTM_X,
		Mat& UTM_Y
	);
	/*
	* @brief 从LVIS 2级数据中读取DTM和DSM信息
	* @param LVIS2_filelist                     LVIS 2级文件
	* @param DTM                                LVIS DTM信息(返回值，n×1)
	* @param DSM                                LVIS DSM信息(RH100，返回值，n×1)
	* @param RH100                              LVIS RH100信息(返回值，n×1)
	* @param RH95                               LVIS RH100信息(返回值，n×1)
	* @param lat                                LVIS 纬度信息(返回值，n×1)
	* @param lon                                LVIS 经度信息(返回值，n×1)
	* @return 成功返回0，否则返回-1
	*/
	int read_LVIS(
		vector<string>& LVIS2_filelist,
		Mat& DTM,
		Mat& DSM,
		Mat& RH100,
		Mat& RH95,
		Mat& lat,
		Mat& lon
	);
	/*
	* @brief 将DTM/DSM数据投影至DLR F-SAR坐标系
	* @param east_min                          F-SAR场景边缘
	* @param north_min                         F-SAR场景边缘
	* @param east_max                          F-SAR场景边缘
	* @param north_max                         F-SAR场景边缘
	* @param projection_zone                   UTM区号
	* @param pixel_spacing                     参考DEM采样间隔（米）
	* @param sr2geo_az                         参考DEM在SAR坐标系中的方位向坐标表
	* @param sr2geo_rg                         参考DEM在SAR坐标系中的距离向坐标表
	* @param sr2geo_h_ref                      参考DEM的高度
	* @param sr2geo3d_rg_o1                    3D地理编码系数
	* @param sr2geo3d_rg_o2                    3D地理编码系数
	* @param sr2geo3d_az_o1                    3D地理编码系数
	* @param sr2geo3d_az_o2                    3D地理编码系数
	* @param DTM/DSM                           待投影的DTM/DSM
	* @param DTM_lon                           待投影DTM/DSM的经度
	* @param DTM_lat                           待投影DTM/DSM的纬度
	* @param mapped_slc_rg                     投影后DTM/DSM在SAR坐标系中的距离向坐标（返回值）
	* @param mapped_slc_az                     投影后DTM/DSM在SAR坐标系中的方位向坐标（返回值）
	* @param mapped_h0                         参考DEM（返回值，与mapped_slc_rg和mapped_slc_az同尺寸）
	*/
	int geo2sar_DLR(
		double east_min,
		double north_min,
		double east_max,
		double north_max,
		int projection_zone,
		double pixel_spacing,
		Mat& sr2geo_az,
		Mat& sr2geo_rg,
		Mat& sr2geo_h_ref,
		Mat& sr2geo3d_rg_o1,
		Mat& sr2geo3d_rg_o2,
		Mat& sr2geo3d_az_o1,
		Mat& sr2geo3d_az_o2,
		Mat& DTM,
		Mat& DTM_lon,
		Mat& DTM_lat,
		Mat& mapped_slc_rg,
		Mat& mapped_slc_az,
		Mat& mapped_h0
	);
	// 根据经纬度获取大地水准面高差
	static double getGeoidHeight(
		const std::string& geoidFilePath,
		double lon, 
		double lat
	);
private:
	static constexpr const char* SRTMURL = "https://srtm.csi.cgiar.org/wp-content/uploads/files/srtm_5x5/TIFF/";
	static constexpr const char* error_head = "UTILS_DLL_ERROR: error happens when using ";
	static constexpr const char* parallel_error_head = "UTILS_DLL_ERROR: error happens when using parallel computing in function: ";

};


#endif