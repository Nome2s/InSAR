#pragma once
#ifndef __UTILS__H__
#define __UTILS__H__
#include"..\include\Package.h"
#include"..\include\ComplexMat.h"
#include<fstream>
#include<iostream>
#include<string>
#include"..\include\sar_comm.h"
#define INPUTMAXSIZE 1024
#define PI 3.141592653589793238
#define VEL_C 299792458.0
/*********************************************************/
/*                Delaunay������ �ڵ���                  */
/*********************************************************/
class InSAR_API tri_node
{
public:
	/*Ĭ�Ϲ��캯��*/
	tri_node();
	/*�������캯��*/
	tri_node(const tri_node& node);
	/*���캯��
	* ����1 �ڵ�����
	* ����2 �ڵ�����
	* ����3 �ڵ��ڽӱ���
	* ����4 �ڵ���λ
	*/
	tri_node(int, int, int, double);
	~tri_node();
	/*��ֵ�����������ֵ��*/
	tri_node operator = (const tri_node& src);
	/*��ȡ�ڵ���λ
	* ����1 ��λָ�루����ֵ��
	*/
	int get_phase(double* phi) const;
	/*��ȡ�ڵ���������
	* ����1 �����
	* ����2 �����
	*/
	int get_pos(int* rows, int* cols) const;
	/*�ڵ���λ��ֵ
	* ����1 ������λ
	*/
	int set_phase(double phi);
	/*��ȡ�ڽӱ�ָ��
	* ����1 ָ���ڽӱ�ָ���ָ�루����ֵ��
	* ����2 �ڽӱ߸���ָ�루����ֵ��
	*/
	int get_neigh_ptr(long** ptr2ptr, int* num) const;
	/*�ı���״̬
	* ����1 �Ƿ��Ѿ����
	*/
	int set_status(bool b_unwrapped);
	/*�ı�ƽ��״̬
	* ����1 �Ƿ����ڲв�ƽ��������
	*/
	int set_balance(bool b_balanced);
	/*��ӡ�ڽӱ����
	* 
	*/
	int print_neighbour() const;
	/*��ȡ�ڽӱ߸���
	* ����1 �ڽӱ߸���ָ��
	*/
	int get_num_neigh(int* num_neigh) const;
	/*��ȡ����һ�ڵ�ľ���
	* ����1 ��һ�ڵ�
	* ����2 ����
	*/
	int get_distance(tri_node node, double* distance) const;
	/*��ȡ���״̬
	* ����ֵ���Ƿ��ѽ����
	*/
	bool get_status() const;
	/*��ȡƽ��״̬
	* ����ֵ���Ƿ�ƽ�⣬Ĭ���ǣ�
	*/
	bool get_balance() const;
	/*�����Ƿ�ڵ����ڲв�������
	*/
	bool is_residue_node() const;
	/*���ýڵ��Ƿ����ڲв�ڵ�
	*/
	int set_residue(bool b_res);
	/*��ȡ�α�����*/
	double get_vel() const;
	/*��ȡ�߳����*/
	double get_height() const;
	/*�����α�����*/
	int set_vel(double vel);
	/*���ø߳����*/
	int set_height(double height);

private:

	/*****************InSAR�������*******************/

	/*�Ƿ��ѽ��(Ĭ��δ���)*/
	bool b_unwrapped;
	/*�Ƿ����ڲв�ڵ�*/
	bool b_residue;
	/*�Ƿ�����ƽ�������εĶ��㣨Ĭ��Ϊ�ǣ���ͬʱ��PS-InSAR�г䵱�Ƿ�ڵ㱻�����ı�־(Ϊtrue��ʾ���������� Ϊfalse��ʾ������)*/
	bool b_balanced;
	/*�ڵ���������ʼֵΪ0��*/
	int rows;
	/*�ڵ���������ʼֵΪ0��*/
	int cols;
	/*�ڵ��ڽӱ���*/
	int num_neigh_edges;
	/*�ڵ���λ*/
	double phase;
	/*�ڵ��ڽӱ����*/
	long* neigh_edges;

	/*****************PS-InSAR�������*******************/
	
	/*�α�����*/
	double vel;
	/*�߳����*/
	double epsilon_height;
};

/*********************************************************/
/*             Delaunay������ �����νṹ��               */
/*********************************************************/
struct triangle
{
	/*���������*/
	int num;
	/*��1*/
	int p1;
	/*��2*/
	int p2;
	/*��3*/
	int p3;
	/*�����βв�ֵ*/
	double residue;
	/*�������������1*/
	int neigh1;
	/*�������������2*/
	int neigh2;
	/*�������������3*/
	int neigh3;
	/*��1����1��ʼ��*/
	int edge1;
	/*��2����1��ʼ��*/
	int edge2;
	/*��3����1��ʼ��*/
	int edge3;

	/*Ĭ�Ϲ��캯��*/
	triangle()
	{
		num = p1 = p2 = p3 = neigh1 = neigh2 = neigh3 = edge1 = edge2 = edge3 = 0;
		residue = 0.0;
	}
	/*�������캯��*/
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
	/*��ֵ(���)*/
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
/*             Delaunay������ �����α߽ṹ��             */
/*********************************************************/
struct tri_edge
{
	/**********InSAR����**********/

	/*�������棨��Ŵ�С����Ϊ����*/
	double gain;
	/*��λ��������������ͼ�������*/
	double quality;
	/*�����к�*/
	int num;
	/*�˵�1*/
	int end1;
	/*�˵�2*/
	int end2;
	/*�в�߱�־*/
	bool isResidueEdge;
	/*����߽��־*/
	bool isBoundry;


	/**********PS_InSAR����**********/

	/*�����α��ٶȲ�ϵ����4 * pi / lambda * Ti��*/
	//double coef_delta_vel;
	/*�߳����ϵ����4 * pi * bperp_i / lambda / R_i / sin_theta_i  ��*/
	//double coef_delta_height;
	/*�����α��ٶȲ�(����Ϊ������ - С����)*/
	double delta_vel;
	/*�߳����(����Ϊ������ - С����)*/
	double delta_height;
	/*ģ�����ϵ��*/
	double MC;
	/*�˵���λ���λ���Ϊ������Ŷ˵��С��Ŷ˵㣩*/
	double phase_diff;

	/*Ĭ�Ϲ��캯��*/
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
	/*�������캯��*/
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
	/*��ֵ�����������ֵ��*/
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
/*          Delaunay������ �����α����кŽṹ��          */
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
/*                   ��������ڵ�ṹ��                  */
/*-------------------------------------------------------*/
struct node_index
{
	/*�ڵ���������0��ʼ��*/
	int row;
	/*�ڵ���������0��ʼ��*/
	int col;
	/*�ڵ���λ����*/
	double quality;
	/*Ĭ�Ϲ��캯��*/
	node_index()
	{
		row = 0; col = 0; quality = 0.0;
	}
	/*�������캯��*/
	node_index(const node_index& cp)
	{
		this->row = cp.row; this->col = cp.col; this->quality = cp.quality;
	}
	/*��ֵ����*/
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

/*-------------------------------------------------------*/
/*                    ��άλ��ʸ��                       */
/*-------------------------------------------------------*/
struct Position
{
	double x;
	double y;
	double z;
	Position()
	{
		this->x = 0.0;
		this->y = 0.0;
		this->z = 0.0;
	}
	/*��ֵ���캯��*/
	Position(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	/*�������캯��*/
	Position(const Position& cp)
	{
		this->x = cp.x;
		this->y = cp.y;
		this->z = cp.z;
	}
	/*��ֵ����(���)*/
	Position operator=(const Position& cp)
	{
		this->x = cp.x;
		this->y = cp.y;
		this->z = cp.z;
		return *this;
	}

};

/*-------------------------------------------------------*/
/*                    ��ά�ٶ�ʸ��                       */
/*-------------------------------------------------------*/
struct Velocity
{
	double vx;
	double vy;
	double vz;
	Velocity()
	{
		this->vx = 0.0;
		this->vy = 0.0;
		this->vz = 0.0;
	}
	/*��ֵ���캯��*/
	Velocity(double vx, double vy, double vz)
	{
		this->vx = vx;
		this->vy = vy;
		this->vz = vz;
	}
	/*�������캯��*/
	Velocity(const Velocity& cp)
	{
		this->vx = cp.vx;
		this->vy = cp.vy;
		this->vz = cp.vz;
	}
	/*��ֵ����(���)*/
	Velocity operator=(const Velocity& cp)
	{
		this->vx = cp.vx;
		this->vy = cp.vy;
		this->vz = cp.vz;
		return *this;
	}

};

/*-------------------------------------------------------*/
/*                   ���ǹ����Ϣ                        */
/*-------------------------------------------------------*/
struct OSV
{
	double time;
	double x;
	double y;
	double z;
	double vx;
	double vy;
	double vz;
	OSV()
	{
		time = x = y = z = vx = vy = vz = 0.0;
	}
	OSV(double time, double x, double y, double z, double vx, double vy, double vz)
	{
		this->time = time;
		this->x = x;
		this->y = y;
		this->z = z;
		this->vx = vx;
		this->vy = vy;
		this->vz = vz;
	}
	/*�������캯��*/
	OSV(const OSV& osv)
	{
		this->time = osv.time;
		this->x = osv.x;
		this->y = osv.y;
		this->z = osv.z;
		this->vx = osv.vx;
		this->vy = osv.vy;
		this->vz = osv.vz;
	}
	/*��ֵ����*/
	OSV operator=(const OSV& osv)
	{
		this->time = osv.time;
		this->x = osv.x;
		this->y = osv.y;
		this->z = osv.z;
		this->vx = osv.vx;
		this->vy = osv.vy;
		this->vz = osv.vz;
		return *this;
	}

};


/*********************************************************/
/*               ����SAR��������������                 */
/*********************************************************/
class InSAR_API Utils
{
public:
	Utils();
	~Utils();
	/*@brief ���ɷ����ɾ���
	* @param inArray                           �Ա�������
	* @param vandermondeMatrix                 �����ɾ���
	* @param degree                            ����
	* @return �ɹ�����-1�����򷵻�0
	*/
	static int createVandermondeMatrix(
		Mat& inArray,
		Mat& vandermondeMatrix,
		int degree
	);
	/*@brief ����ʽ��ϣ�Ax=b��
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
	/** @brief ��int�;��������
	
	@param input                  �������int�ͣ�
	@param out                    ������
	@return �ɹ�����0�����򷵻�-1
	*/
	int get_mode_index(const Mat& input, int* out);
	/*��������ݶ�
	 ����1 Դ����
	 ����2 �з����ݶȣ�����ֵ��
	 ����3 �з����ݶȣ�����ֵ��
	 ����4 �Ƿ���ʹ���ݶȾ����Դ�����С��ͬ��Ĭ�ϲ��㣩
	*/
	int diff(Mat& Src, Mat& diff_1, Mat& diff_2, bool same = true);
	/*���������λ
	 ����1 ��ͼ�񣨸���
	 ����2 ��ͼ�񣨸���
	 ����3 ������λ������ֵ��
	*/
	int generate_phase(const ComplexMat& Master, const ComplexMat& Slave, Mat& phase);

	/** @brief �����Ȼ��ɹ�����
	 
	@param master_image                       ��ͼ�񣨸���
	@param slave_image                        ��ͼ�񣨸���
	@param coherence                          ���ϵ��������ֵ��
	@return �ɹ�����0�����򷵻�-1
	*/
	int real_coherence(ComplexMat& master_image, ComplexMat& slave_image, Mat& coherence);
	/** @brief �����Ȼ��ɹ������������ƴ��ڳߴ�ӿڣ�
	
	@param master_image                       ��ͼ�񣨸���
	@param slave_image                        ��ͼ�񣨸���
	@param est_wndsize_rg                     ���ƴ��ھ�����ߴ磨������
	@param est_wndsize_az                     ���ƴ��ڷ�λ��ߴ磨������
	@param coherence                          ���ϵ��������ֵ��
	*/
	int real_coherence(
		const ComplexMat& master_image,
		const ComplexMat& slave_image,
		int est_wndsize_rg,
		int est_wndsize_az,
		Mat& coherence
	);
	/** @brief Ƶ���޹���ɹ�����
	
	 @param master_image                        ��ͼ�񣨸���
	 @param slave_image                         ��ͼ�񣨸���
	 @param coherence                           ���ϵ��������ֵ��
	 @return �ɹ�����0�����򷵻�-1
	*/
	int complex_coherence(ComplexMat& master_image, ComplexMat& slave_image, Mat& coherence);
	/** @brief Ƶ���޹���ɹ������������ƴ��ڳߴ�ӿڣ�
	
	@param master_image                         ��ͼ��
	@param slave_image                          ��ͼ��
	@param est_wndsize_rg                       ���ƴ��ھ�����ߴ磨������
	@param est_wndsize_az                       ���ƴ��ڷ�λ��ߴ磨������
	@param coherence                            ���ϵ��������ֵ��
	@return �ɹ�����0�����򷵻�-1
	*/
	int complex_coherence(
		const ComplexMat& master_image,
		const ComplexMat& slave_image,
		int est_wndsize_rg,
		int est_wndsize_az,
		Mat& coherence
	);
	/** @brief ���ݸ�����λ�����ϵ��
	@param phase                          ������λ
	@param coherence                      ���ϵ��������ֵ��
	@return �ɹ�����0�����򷵻�-1
	*/
	int phase_coherence(Mat& phase, Mat& coherence);
	/** @brief ���ݸ�����λ�����ϵ���������ƴ��ڳߴ�ӿڣ�
	
	@param phase                          ������λ
	@param est_wndsize_rg                 ���ƴ��ھ�����ߴ磨������
	@param est_wndsize_az                 ���ƴ��ڷ�λ��ߴ磨������
	@param coherence                      ���ϵ��������ֵ��
	@return �ɹ�����0�����򷵻�-1
	*/
	int phase_coherence(
		const Mat& phase,
		int est_wndsize_rg,
		int est_wndsize_az,
		Mat& coherence
	);
	/*�����λ��������
	* ����1 ������λ
	* ����2 ��λ�����������ֵ��
	* ����3 ���㴰�ڴ�С��������
	*/
	int phase_derivatives_variance(Mat& phase, Mat& phase_derivatives_variance, int wndsize = 3);
	/*FFTSHIFT
	 ����1 ��fftshift�ľ���ԭ�ؽ���fftshift������
	*/
	int fftshift(Mat& matrix);
	/*���������λͼ�Ĳв�ֵ���㣩
	 ����1 ������λ
	 ����2 �в����󣨷���ֵ��
	*/
	int residue(Mat& phase, Mat& residue);
	/*����Delaunay��������Ĳв�ֵ�����ұ�ע�в�ߺͲв�ڵ�,���ڽ��ʱ�ܿ���
	* ����1 Delaunay�����������νṹ������
	* ����2 Delaunay����������������
	* ����3 Delaunay�������ڵ�����
	* ����4 Delaunay�������߽ṹ������
	* ����5 Delaunay������������
	*/
	int residue(triangle* tri, int num_triangle, vector<tri_node>& nodes, tri_edge* edges, int num_edges);
	/** @brief ����Delaunay��������Ĳв�ֵ�����ұ�ע�в�ߺͲв�ڵ㣩
	@param triangle                              Delaunay�����������νṹ������
	@param nodes                                 Delaunay�������ڵ�����
	@param edges                                 Delaunay�������߽ṹ������
	@param distance_thresh                       �߳�����ֵ����������ֵ������в����㣩
	@return �ɹ�����0�����򷵻�-1
	*/
	int residue(
		vector<triangle>& triangle,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges,
		double distance_thresh
	);
	/*����mask��ɸѡ�������㣩
	* ����1 ���ϵ������
	* ����2 mask�پ��󣨷���ֵ��
	* ����3 ���ڰ뾶
	* ����4 ��ֵ
	*/
	int gen_mask(Mat& coherence, Mat& mask, int wnd_size, double thresh);
	/*@brief ������λ����������趨��ֵ�����������Ĥ
	* @param phase_derivatives_variance                   ��λ��������
	* @param mask                                         �����������Ĥ
	* @param wndsize                                      ������Ĥ���ڴ�С
	* @param thresh                                       ��ֵ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int gen_mask_pdv(
		Mat& phase_derivatives_variance,
		Mat& mask,
		int wndsize,
		double thresh
	);
	/*����mask��ɸѡ�������㣩
	* ����1 ���ϵ������
	* ����2 ��λ��������
	* ����3 mask�پ��󣨷���ֵ��
	* ����4 ���ڰ뾶
	* ����5 ���ϵ����ֵ
	* ����6 ��λ����������ֵ
	*/
	int gen_mask(
		Mat& coherence,
		Mat& phase_derivatives,
		Mat& mask, int wnd_size,
		double coh_thresh,
		double phase_derivative_thresh
	);
	/*�����趨��ֵɸѡ�в��
	* ����1 ԭʼ�в�����
	* ����2 ɸѡ��в�����
	* ����3 ɸѡ��ֵ������0��
	* ����4 �в�����
	*/
	int residue_sift(Mat& residue_src, Mat& residue_dst, double thresh, long* num_residue);
	/*������λ����-pi,pi��
	 ����1 ��������λ
	 ����2 ���ƺ����λ������ֵ��
	*/
	int wrap(Mat& Src, Mat& Dst);

	/*���л����ۼƻ���
	 ����1 ����������
	 ����2 ���ַ���(dim = 1,���м��� dim = 2,���м���)
	*/
	int cumsum(Mat& phase, int dim);
	/*������㣨��ά��
	* ����1 ����һ(n * 3)
	* ����2 ������(n * 3)
	* ����3 ���
	*/
	int cross(Mat& vec1, Mat& vec2, Mat& out);
	/*д��DIMACS�ļ���������С�������⣩
	 ����1 Ŀ���ļ���
	 ����2 �в�����
	 ����3 ���ϵ������
	 ����4 �в����ֵ(����0)
	*/
	int write_DIMACS(const char* DIMACS_file_problem, Mat& residue, Mat& coherence, double thresh);
	/*@brief д��DIMACS�ļ��������Ľ�����С���������⣩
	* @param DIMACS_problem_file      Ŀ���ļ�
	* @param residue                  �в�����
	* @param mask                     ����·��������Ĥ(int��)
	* @param cost                     ������
	* @param thresh                   �в����ֵ��Ĭ��Ϊ0.7��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int write_DIMACS(
		const char* DIMACS_problem_file,
		const Mat& residue,
		Mat& mask,
		const Mat& cost,
		double thresh = 0.7
	);
	/*д��DIMACS�ļ���������С�������⣬�������������磩
	* ����1 Ŀ���ļ���
	* ����2 Delaunay�����νṹ������
	* ����3 Delaunay����������
	* ����4 Delaunay�������ڵ�����
	* ����5 Delaunay�������߽ṹ������
	* ����6 Delaunay������������
	* ����7 ÿ���ڵ�ķ���
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
	/** @brief д��DIMACS�ļ���������С�������⣬Delaunay�������磩
	
	@param DIMACS_file_problem                         Ŀ��DIMACS�ļ�
	@param triange                                     Delaunay�����νṹ������
	@param nodes                                       Delaunay�������ڵ�����
	@param edges                                       Delaunay�������߽ṹ������
	@param cost                                        ÿ���ڵ�ķ���
	@return �ɹ�����0�����򷵻�-1
	*/
	int write_DIMACS(
		const char* DIMACS_file_problem,
		vector<triangle>& triangle,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges,
		const Mat& cost
	);
	/*��ȡDIMACS�ļ�����ȡ������������
	 ����1 ��С������������ļ�
	 ����2 ֦��·��1
	 ����3 ֦��·��2
	 ����4 ������λͼ������
	 ����5 ������λͼ������
	*/
	int read_DIMACS(const char* DIMACS_file_solution, Mat& k1, Mat& k2, int rows, int cols);
	/*��ȡDIMACS�ļ�����ȡ������������
	* ����1 ��С������������ļ�
	* ����2 Delaunay�������߽ṹ������
	* ����3 Delaunay������������
	* ����4 Delaunay�������ڵ�����
	* ����5 Delaunay����������������
	* ����6 Delaunay����������������
	*/
	int read_DIMACS(
		const char* DIMACS_file_solution,
		tri_edge* edges,
		int num_edges,
		vector<tri_node>& nodes,
		triangle* tri,
		int num_triangle
	);
	/** @brief ��ȡDIMACS�ļ�����ȡ������������
	
	@param DIMACS_file_solution                         ��С������������ļ�
	@param edges                                        Delaunay�������߽ṹ������
	@param nodes                                        Delaunay�������ڵ�����
	@param triangle                                     Delaunay����������������
	@param return �ɹ�����0�����򷵻�-1
	*/
	int read_DIMACS(
		const char* DIMACS_file_solution,
		vector<tri_edge>& edges,
		vector<tri_node>& nodes,
		vector<triangle>& triangle
	);
	/*��OpenCV Mat�����Զ����Ʒ�ʽд��Ŀ���ļ�
	* ����1 Ŀ���ļ���
	* ����2 ��д������
	*/
	int cvmat2bin(const char* Dst_file, Mat& Src);
	/*�Ӷ������ļ��ж����ݣ���������ת����OpenCV Mat��ʽ
	* ����1 �������ļ�
	* ����2 Ŀ�����
	*/
	int bin2cvmat(const char* Src_file, Mat& Dst);
	/*InSAR���Ӵ�����׼֮����У� �ı�ͼ��ߴ磩
	* ����1 ��ͼ��SLC��
	* ����2 ��ͼ��SLC��
	* ����3 ������λ
	* ����4 ���ӱ���������1��
	*/
	int multilook(ComplexMat& Master, ComplexMat& Slave, Mat& phase, int multilook_times);
	/** @brief InSAR���Ӵ������ı�ͼ��ߴ磩
	
	@param master_slc                    ��ͼ��
	@param slave_slc                     ��ͼ��
	@param multilook_rg                  ��������ӱ���
	@param multilook_az                  ��λ����ӱ���
	@param multilooked_phase             ������λ
	*/
	int multilook(const ComplexMat& master, const ComplexMat& slave, int multilook_rg, int multilook_az, Mat& phase);
	/*@brief InSAR���Ӵ����ı䴰�ڳߴ磩
	* @param master                      ��ͼ��
	* @param slave                       ��ͼ��
	* @param multilook_rg                ��������ӱ���
	* @param multilook_az                ��λ����ӱ���
	* @param phase                       ������λ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int Multilook(
		const ComplexMat& master, 
		const ComplexMat& slave, 
		int multilook_rg, 
		int multilook_az,
		Mat& phase
	);
	/*@brief ��λ���Ӵ���(�ı�ߴ�)
	* @param phase                      ��������λ
	* @param outPhase                   ������
	* @param multi_rg                   ��������ӱ���
	* @param multi_az                   ��λ����ӱ���
	* @return �ɹ�����0�����򷵻�-1
	*/
	int multilook(
		const Mat& phase,
		Mat& outPhase,
		int multi_rg,
		int multi_az
	);
	/*@brief SARͼ�����
	* @param amplitude                 SARͼ�����ͼ
	* @param outAmplitude              ����SARͼ��
	* @param multilook_rg              ��������ӱ���
	* @param multilook_az              ��λ����ӱ���
	* @return �ɹ�����0�����򷵻�-1
	*/
	int multilook_SAR(
		const Mat& amplitude,
		Mat& outAmplitude,
		int multilook_rg,
		int multilook_az
	);
	/** @brief ����λת����cos��sin��ʵ�����鲿��֧��double��float��
	
	@param phase                     ������λ
	@param cos                       ʵ��
	@param sin                       �鲿
	@return �ɹ�����0�����򷵻�-1
	*/
	int phase2cos(const Mat& phase, Mat& cos, Mat& sin);
	/*84����ϵת��γ������ϵ
	* ����1 84����ϵ����
	* ����2 ��γ������ϵ���꣨��/��/�ף�
	*/
	int xyz2ell(Mat xyz, Mat& llh);
	/*��γ������ϵת84����ϵ
	* ����1 ��γ������ϵ���꣨γ��/����/�߶ȣ�
	* ����2 84����ϵ����
	*/
	int ell2xyz(Mat llh, Mat& xyz);
	/*@brief ��/γ/�� ---> x/y/z
	* @param lon                 ����
	* @param lat                 γ��
	* @param elevation           �߶�
	* @param xyz                 x/y/z
	* @return �ɹ�����0�����򷵻�-1
	*/
	static int ell2xyz(double lon, double lat, double elevation, Position& xyz);



	/*******************************************************/
	/*                     ͼ��洢���߼�                  */
	/*******************************************************/

	/*��������SLC����ͼ
	* ����1 Ŀ���ļ���
	* ����2 �����������������ӷ�ΧdB��
	* ����3 ���Ӹ�ͼ��
	*/
	int saveSLC(const char* filename, double db, ComplexMat& SLC);
	/*@brief SARͼ������
	* @param filename       ����Ŀ���ļ�
	* @param db             ������̬��Χ
	* @param slc            ���Ӹ�ͼ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int SAR_image_quantify(const char* filename, double db, ComplexMat& SLC);
	/*@brief ��������SAR����ͼ
	* @param filename             �����ļ���
	* @param amplitude            ��������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int saveAmplitude(
		const char* filename,
		Mat& amplitude
	);
	/*���������λͼ
	* ����1 Ŀ���ļ���
	* ����2 ��ɫӳ�䣨jet/hsv/cool/parula�ȣ�
	* ����3 ��������λ
	*/
	int savephase(const char* filename, const char* colormap, Mat phase);
	/*���������λͼ
	* ����1 Ŀ���ļ���
	* ����2 ��ɫӳ�䣨jet/hsv/cool/parula�ȣ�
	* ����3 ��������λ
	*/
	int save_coherence(const char* filename, const char* colormap, Mat coherence);
	/*@brief ���������λͼ����Ĥ����Ϊ��ɫ��
	* @param filename                            Ŀ���ļ���
	* @param colormap                            ��ɫӳ�䣨jet/hsv/cool/parula�ȣ�
	* @param phase                               ��������λ
	* @param mask                                (int��)
	* @return �ɹ�����0�����򷵻�-1
	*/
	int savephase_black(const char* filename, const char* colormap, Mat& phase, Mat& mask);
	/*@brief ���������λͼ����Ĥ����Ϊ��ɫ��
	* @param filename                            Ŀ���ļ���
	* @param colormap                            ��ɫӳ�䣨jet/hsv/cool/parula�ȣ�
	* @param phase                               ��������λ
	* @param mask                                (int��)
	* @return �ɹ�����0�����򷵻�-1
	*/
	int savephase_white(const char* filename, const char* colormap, Mat& phase, Mat& mask);
	/*ͼ���ز���
	* ����1 ԭͼ��
	* ����2 Ŀ��ͼ��
	* ����3 Ŀ��ͼ��߶�
	* ����4 Ŀ��ͼ����
	*/
	int resampling(const char* Src_file, const char* Dst_file, int dst_height, int dst_width);
	/*����SARͼ���������λ����
	* ����1 ����SARͼ��
	* ����2 ������λͼ
	* ����3 ����ͼ��
	* ����4 SARͼ��ռ��
	*/
	int amplitude_phase_blend(
		const char* amplitude_file,
		const char* phase_file,
		const char* blended_file,
		double SAR_ratio = 0.9
	);



	/*******************************************************/
	/*                Delaunay��������غ�����             */
	/*******************************************************/

	/*��.edge�ļ���ȡDelaunay�������ı���Ϣ
	* ����1 .edge�ļ�
	* ����2 ָ��߽ṹ���ָ�루����ֵ���ڴ���Ҫ�ֶ��ͷţ�
	* ����3 ָ��߸�����ָ�루����ֵ��
	* ����4 ͳ��ÿ���ڵ���ڽӱ���������ֵ���ڴ���Ҫ�ֶ��ͷţ�
	* ����5 �ڵ���
	*/
	int read_edges(const char* filename, tri_edge** edges, long* num_edges, int** neighbours, long num_nodes);
	/** @brief ��.edge�ļ���ȡDelaunay�������ı���Ϣ
	
	@param edge_file               .edge�ļ�
	@param num_nodes               �ڵ���
	@param edges                   Delaunay�����������飨����ֵ��
	@param node_neighbours         ÿ���ڵ���ڽӱ���������ֵ��
	@return  �ɹ�����0�� ���򷵻�-1
	*/
	int read_edges(
		const char* edge_file,
		vector<tri_edge>& edges,
		vector<int>& node_neighbours,
		long num_nodes
	);
	/*��ʼ��Delaunay�������ڵ�
	* ����1 �ڵ����飨����ֵ��
	* ����2 ��λ(double��)
	* ����3 ��λmask��int �ͣ�
	* ����4 edges�ṹ������
	* ����5 edges����
	* ����6 ÿ���ڵ���ڽӱ���Ϣ
	* ����7 �ڵ���
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
	/** @brief ��ʼ��Delaunay�������ڵ�
	
	@param node_array                 �ڵ����飨����ֵ��
	@param phase                      ��λֵ
	@param mask                       ��λ��Ĥ
	@param edges                      Delaunay��������߽ṹ������
	@param node_neighbours            ÿ���ڵ���ڱ߸���
	@param num_nodes                  �ڵ���
	@return �ɹ�����0�����򷵻�-1
	*/
	int init_tri_node(
		vector<tri_node>& node_array,
		const Mat& phase,
		const Mat& mask,
		const vector<tri_edge>& edges,
		const vector<int>& node_neighbours,
		int num_nodes
	);
	/** @brief ��ʼ��Delaunay�����������λ��
	
	@param edges                  Delaunay������������飨�Ѿ�ʹ��read_edges������ʼ�����ģ�
	@param node_array             Delaunay��������ڵ����飨�Ѿ�ʹ��init_tri_node������ʼ�����ģ�
	@return �ɹ�����0�����򷵻�-1
	*/
	int init_edge_phase_diff(
		vector<tri_edge>& edges,
		const vector<tri_node>& node_array
	);
	/*��ʼ��Delaunay�������ߵ���λ����
	* ����1 ��λ����ͼ
	* ����2 Delaunay�������߽ṹ������ָ��
	* ����3 Delaunay�������߽ṹ�������С
	* ����4 Delaunay�������ڵ�����
	*/
	int init_edges_quality(Mat& quality, tri_edge* edges, int num_edges, vector<tri_node>& nodes);
	/** @brief ��ʼ��Delaunay�������ߵ���λ����ָ��
	
	@param quality_index                  ��λ����ͼָ��������λ�����෴��
	@param edges                          Delaunay�������߽ṹ������
	@param nodes                          Delaunay�������ڵ�����
	@return �ɹ�����0�� ���򷵻�-1
	*/
	int init_edges_quality(
		const Mat& quality_index,
		vector<tri_edge>& edges,
		const vector<tri_node>& nodes
	);
	/*��.ele�ļ���.neigh�ļ���ȡDelaunay����������������Ϣ
	* ����1 .ele�ļ�
	* ����2 .neigh�ļ�
	* ����3 �����νṹ������ָ�루����ֵ, �ڴ���Ҫ�ֶ��ͷţ�
	* ����4 �����θ���������ֵ��
	* ����5 Delaunay�������ڵ�����
	* ����6 Delaunay������������
	* ����7 Delaunay������������
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
	/** @brief ��.ele�ļ���.neigh�ļ���ȡDelaunay����������������Ϣ
	
	@param ele_file                        .ele�ļ�
	@param neigh_file                      .neigh�ļ�
	@param triangle                        �����νṹ�����飨����ֵ��
	@param nodes                           Delaunay�������ڵ�����
	@param edges                           Delaunay������������
	@return �ɹ�����0�����򷵻�-1
	*/
	int read_triangle(
		const char* ele_file,
		const char* neigh_file,
		vector<triangle>& triangle,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges
	);
	/*����Delaunay������
	* ����1 .node�ļ�
	* ����2 triangle.exe����·��
	*/
	int gen_delaunay(const char* filename, const char* exe_path);
	/*д.node�ļ�
	* ����1 .node�ļ�
	* ����2 �ڵ�����
	*/
	int write_node_file(const char* filename, const Mat& mask);




	/*********************************************************/
    /*                PS-InSAR ���ú���                      */
    /*********************************************************/

	/*������ָ����ɸѡPS�㣨D_A��
	* ����1 SAR���Ⱦ�����
	* ����2 ��������ֵ
	* ����3 mask������������PS��λ��maskΪ1������Ϊ0��
	*/
	int PS_amp_dispersion(const vector<Mat>& amplitude, double thresh, Mat& mask);
	/*fifth-order butterworth filter����װ�����˹�˲�����
	* ����1 grid_size
	* ����2 n_win
	* ����3 low_pass_wavelength
	* ����4 �˲���ϵ��������ֵ��
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
	/*��ά����Ҷ�任
	* ����1 �������
	* ����2 ������
	*/
	int fft2(Mat& Src, Mat& Dst);
	/*������ά����Ҷ�任
	* ����1 �������
	* ����2 ������
	*/
	int fft2(ComplexMat& src, ComplexMat& dst);
	/*���ά����Ҷ�任
	* ����1 �������
	* ����2 ������
	*/
	int ifft2(ComplexMat& src, ComplexMat& dst);
	/*���׼��
	* ����1 �������
	* ����2 ��׼���ֵ
	*/
	int std(const Mat& input, double* std);
	/*�ü�����Ȥ��SARͼ������AOI��
	* ����1 SARͼ�������ļ�����img��ʽ��
	* ����2 �ü����SARͼ�����б���·��
	* ����2 AOI����γ��/����/�߶�(1��3)
	* ����3 AOI��������
	* ����4 AOI�ߣ�������
	*/
	int PS_cut_AOI(
		vector<string>& SAR_images_files,
		const char* save_path,
		Mat& llh,
		int rows,
		int cols
	);
	/** @brief ʱ��SARͼ��������׼(����slcͬʱ�����ڴ�)
	
	@param SAR_images            ʱ��SARͼ��inplace��ԭ�ز�����
	@param offset                ��׼�����Ͻ�ƫ����(�ߴ磺n_images �� 2) 
	@param Master_index          ��ͼ�����(��Ŵ�1��ʼ)
	@param coh_method            ����ʵ��ػ��Ǹ���أ�0����ʵ��أ� 1������أ�
	@param interp_times          ��ֵ������2��n���ݣ�
	@param blocksize             �ӿ��С��2��n���ݣ�
	*/
	int stack_coregistration(
		vector<ComplexMat>& SAR_images,
		Mat& offset,
		int Master_index,
		int coh_method,
		int interp_times,
		int blocksize
	);
	/** @brief ʱ��SARͼ��������׼(slc���������ڴ棬�Խ�ʡ�ڴ�)
	
	@param SAR_images            ʱ��SARͼ���ļ�
	@param SAR_images_out        ��׼����ļ�
	@param offset                ��׼�����Ͻ�ƫ����(�ߴ磺n_images �� 2)
	@param Master_index          ��ͼ�����(��Ŵ�1��ʼ)
	@param interp_times          ��ֵ������2��n���ݣ�
	@param blocksize             �ӿ��С��2��n���ݣ�
	*/
	int stack_coregistration(
		vector<string>& SAR_images,
		vector<string>& SAR_images_out,
		Mat& offset,
		int Master_index,
		int interp_times,
		int blocksize
	);
	/** @brief ʱ��SARͼ��������׼�����С��ֿ���׼��֧��16λ���ͺ�64λ���������룩
	* 
	* @param SAR_images                     ʱ��SARͼ���ļ�
	* @param SAR_images_out                 ��׼����ļ�
	* @param Master_index                   ��ͼ����ţ���1��ʼ��
	* @param interp_times                   ��ֵ������2��n���ݣ�
	* @param blocksize                      �ӿ��С��2��n���ݣ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int stack_coregistration(
		vector<string>& SAR_images,
		vector<string>& SAR_images_out,
		int Master_index,
		int interp_times,
		int blocksize
	);
	/*hist������ͳ��ֱ��ͼ������
	* ����1 ��ͳ������
	* ����2 ͳ�Ʊ�׼������������
	* ����3 ͳ�Ʊ�׼������������
	* ����4 ����뾶��n * ����뾶 = ��ͳ�Ʊ�׼������������ - ͳ�Ʊ�׼�����������ģ���
	* ����5 ͳ�����
	*/
	int hist(
		Mat& input,
		double lowercenter,
		double uppercenter,
		double interval,
		Mat& out
	);
	/*@brief ֱ��ͼͳ�ƺ���
	* @param input                   �����ͳ������
	* @param lowerbound              �����½�
	* @param upperbound              �����Ͻ�
	* @param interval                ͳ��������
	* @param out_x                   �������������꣩
	* @param out_y                   �������������꣩
	* @return �ɹ�����0�����򷵻�-1
	*/
	int hist(
		Mat& input,
		double lowerbound,
		double upperbound,
		double interval,
		Mat& out_x,
		Mat& out_y
	);
	/*@brief ��˹�������
	* @param input_x                ���������
	* @param input_y                ����������
	* @param mu                     ��ֵ
	* @param sigma_square           ����
	* @param scale                  ����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int gaussian_curve_fit(
		Mat& input_x,
		Mat& input_y,
		double* mu,
		double* sigma_square,
		double* scale
	);
	/*
	* ���ǹ����ֵ
	* ����1�����ǹ��������δ��ֵ��
	* ����2����ֵʱ������s��
	* ����3����ֵ���
	*/
	int stateVec_interp(Mat& stateVec, double time_interval, Mat& stateVec_interp);
	/*
	* ��h5��SLC��ͼ���ļ��вü�AOI
	* ����1��h5�ļ�
	* ����2��AOI���ϽǾ���
	* ����3��AOI���Ͻ�γ��
	* ����4��AOI���½Ǿ���
	* ����5��AOI���½�γ��
	* ����6��������Ӹ�ͼ��
	* ����7��AOI���Ͻ���ƫ��������0��ʼ��0����ƫ�ƣ�
	* ����8��AOI���Ͻ���ƫ��������0��ʼ��0����ƫ�ƣ�
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
	/** @brief ��h5��SLC���ļ��вü���AOI����
	
	@param h5_file h5�ļ�
	@param lon_center AOI���ľ���
	@param lat_center AOI����γ��
	@param width AOI��ȣ�m��
	@param height AOI�߶ȣ�m��
	@param slc �ü����slc
	@param offset_row AOI���Ͻ���ԭͼ������ƫ��������0��ʼ��0����ƫ�ƣ�
	@param offset_col AOI���Ͻ���ԭͼ������ƫ��������0��ʼ��0����ƫ�ƣ�
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
	/** @brief ��h5��SLC���ļ��л�ȡ�ü�AOI����ĳߴ�

	@param h5_file          h5�ļ�
	@param lon_center       AOI���ľ���
	@param lat_center       AOI����γ��
	@param width            AOI��ȣ�m��
	@param height           AOI�߶ȣ�m��
	@param AOI_rows         AOI����
	@param AOI_cols         AOI����
	@param offset_row       AOI���Ͻ���ԭͼ������ƫ��������0��ʼ��0����ƫ�ƣ�
	@param offset_col       AOI���Ͻ���ԭͼ������ƫ��������0��ʼ��0����ƫ�ƣ�
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
	/** @brief ����ת�����ߺ���
	
	@param coefficient       ת��ϵ������
	@param coord_in_1        ԭ�������1(1��2��˳�����Ҫ������/��������ǰ)
	@param coord_in_2        ԭ�������2
	@param coord_out         ת���������
	*/
	int coord_conversion(
		Mat& coefficient,
		Mat& coord_in_1,
		Mat& coord_in_2,
		Mat& coord_out
	);
	/** @brief ���߹���

	@param stateVec1               ���ǹ����δ��ֵ��
	@param stateVec2               ���ǹ����δ��ֵ��
	@param lon_coef                ��������ת��ϵ����ͼ������-->���ȣ�
	@param lat_coef                ��������ת��ϵ����ͼ������-->γ�ȣ�
	@param offset_row              ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param offset_col              ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param scene_height            �����߶�(��������)
	@param scene_width             �������(��������)
	@param interp_interval1        ���ǹ����ֵʱ������1/prf��
	@param interp_interval2        ���ǹ����ֵʱ������1/prf��
	@param B_effect                ��ֱ���߳��ȣ�����ֵ��
	@param B_parallel              ƽ�л��߳��ȣ�����ֵ��
	@param sigma_B_effect          ��ֱ���߹��Ʊ�׼�����ֵ��
	@param sigma_B_parallel        ƽ�л��߹��Ʊ�׼�����ֵ��
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
	/** @brief ���߹���

	@param stateVec1               ���ǹ����δ��ֵ��
	@param stateVec2               ���ǹ����δ��ֵ��
	@param lon_center              ��ͼ�񳡾��������꣨���ȣ�
	@param lat_center              ��ͼ�񳡾��������꣨ά�ȣ�
	@param offset_row              ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param offset_col              ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param scene_height            �����߶�(��������)
	@param scene_width             �������(��������)
	@param interp_interval1        ���ǹ����ֵʱ������1/prf��
	@param interp_interval2        ���ǹ����ֵʱ������1/prf��
	@param B_effect                ��ֱ���߳��ȣ�����ֵ��
	@param B_parallel              ƽ�л��߳��ȣ�����ֵ��
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
	/** @brief ���߹���

	@param stateVec1               ���ǹ����δ��ֵ��
	@param stateVec2               ���ǹ����δ��ֵ��
	@param lon_center              ��ͼ�񳡾��������꣨���ȣ�
	@param lat_center              ��ͼ�񳡾��������꣨ά�ȣ�
	@param dem_center              ��ͼ�񳡾��������꣨�߶ȣ�
	@param offset_row              ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param offset_col              ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param scene_height            �����߶�(��������)
	@param scene_width             �������(��������)
	@param interp_interval1        ���ǹ����ֵʱ������1/prf��
	@param interp_interval2        ���ǹ����ֵʱ������1/prf��
	@param B_effect                ��ֱ���߳��ȣ�����ֵ��
	@param B_parallel              ƽ�л��߳��ȣ�����ֵ��
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
	/*@brief ��ؾ���ͬ�ʼ��� + phase linking
	* @param slc_stack                           ������SLC���ݶ�ջ��֧��32λfloat���������ͣ�
	* @param slc_stack_filtered                  phase-linking��Ľ��������ֵ��
	* @param test_wndsize                        ͬ�ʼ����������ڴ�С��������Ĭ��Ϊ15��
	* @param est_wndsize                         ��ؾ�����ƴ��ڴ�С��������Ĭ��Ϊ3��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int homogeneous_selection_and_phase_linking(
		vector<ComplexMat>& slc_stack,
		vector<ComplexMat>& slc_stack_filtered,
		int test_wndsize = 15,
		int est_wndsize = 3
	);
	/*@brief Sum of Kronecker decomposition��SKP�ֽ⣩
	* @param inputMat                            ���ֽ����
	* @param nr1                                 �ֽ����1
	* @param nc1                                 �ֽ����2
	* @param nr2                                 �ֽ����3
	* @param nc2                                 �ֽ����4
	* @param outputMat                           �ֽ����󣨷���ֵ��
	* @return �ɹ�����0�����򷵻�-1
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
	/** @brief ͳ��ͬ�ʼ���
	
	@param pixel1            ��������Ԫ1��������(size: n_images��1)
	@param pixel2            ��������Ԫ2��������(size: n_images��1)
	@param homo_flag         �Ƿ�Ϊͬ����Ԫ(����0��Ϊͬ����Ԫ��-1��Ϊ��ͬ����Ԫ)
	@param alpha             ������ˮƽ�������趨��ֵΪ 0.20,0.15,0.10,0.05,0.025,0.01,0.005,0.001��Ĭ��Ϊ0.05��
	@param method            ���鷽����"KS":Kolmogorov-Smirnov���飬"AD":Anderson-Darling����, Ĭ��ΪKS���飩
	@return                  �������з���0��������-1
	*/
	int homogeneous_test(
		const Mat& pixel1,
		const Mat& pixel2,
		int* homo_flag,
		double alpha = 0.05,
		const char* method = "KS"
	);
	/*@brief ͳ��ͬ�ʼ���
	* @param slc_series      ������SLC���ݶ�ջ
	* @param windsize_az     ���ڴ�С����λ��
	* @param windsize_rg     ���ڴ�С��������
	* @param homo_num        �����ͬ�ʵ������int�;���
	* @param homo_index      ����ͬ�ʵ�mask����(uint8�;���,�����СΪ��nr��nc������windsize_az��windsize_rg��)
	* @param alpha           ������ˮƽ�������趨��ֵΪ 0.20,0.15,0.10,0.05,0.025,0.01,0.005,0.001��Ĭ��Ϊ0.05��
	* @param method          ���鷽����"KS":Kolmogorov-Smirnov���飬"AD":Anderson-Darling����, Ĭ��ΪKS���飩
	* @return �ɹ�����0�����򷵻�-1
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
	/** @brief Hermitian��������ֵ�ֽ�
	
	@param input               ���븴����n��n, double�ͣ�
	@param eigenvalue          ����ֵ��n��1ʵ����,�Ӵ�С���У�
	@param eigenvector         ����������n��n������ ������Ϊ����������
	@return                    �ɹ�����0�����򷵻�-1              
	*/
	int HermitianEVD(
		const ComplexMat& input,
		Mat& eigenvalue,
		ComplexMat& eigenvector
	);
	/** @brief ʱ��SARͼ����ؾ������
	
	@param slc_series               slc���ݶ�ջ
	@param coherence_matrix         ��ؾ��󣨸���, ����ֵ��
	@param est_window_width         ���ƴ��ڿ�ȣ�������
	@param est_window_height        ���ƴ��ڸ߶ȣ�������
	@param ref_row                  ��������ͳ��ͬ�ʼ��飩�ο��������꣬������ͬ�ʼ�������Ҫ�˲���
	@param ref_col                  ��������ͳ��ͬ�ʼ��飩�ο��������꣬������ͬ�ʼ�������Ҫ�˲���
	@param b_homogeneous_test       �Ƿ����ͳ��ͬ�ʼ��飨ͬ�ʼ���ο�����Ĭ��Ϊ�м�����أ�
	@param b_normalize              ������ؾ���ʱslc�����Ƿ��һ������
	@return                         �ɹ�����0�����򷵻�-1 
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
	/** @brief �����ʱ��������λ���ƣ��ֿ��ȡ�����㡢���棩
	
	@param coregis_slc_files              ��׼��SARͼ�����ݶ�ջ���ļ���
	@param phase_files                    ʱ�����и�����λ���ļ�����coregis_slc_files������ͬ����ͼ����λΪ0��
	@param coherence_files                ����ͼ������ͼ��֮������ϵ���ļ����Ƿ�������ϵ��ȡ�����������b_coh_est��
	@param master_indx                    ��ͼ����ţ���1��ʼ��
	@param blocksize_row                  �ӿ�ߴ磨�У��������ͬ�ʼ����������ڰ뾶��
	@param blocksize_col                  �ӿ�ߴ磨�У��������ͬ�ʼ����������ڰ뾶��
	@param out_mask                       ��Ĥ�������Ǿ���EVD�����Ƶ����ص㣬�����thresh_c1_to_c2�йأ�
	@param b_coh_est                      �Ƿ�������ϵ����Ĭ���ǣ�
	@param homogeneous_test_wnd           ͬ�ʼ����������ڴ�С��������homogeneous_test_wnd��homogeneous_test_wnd�� Ĭ��Ϊ21��21��
	@param thresh_c1_to_c2                Э��������2����ֵ���1����ֵ��ֵ��ֵ��0-1֮�䣬Ĭ��Ϊ0.7��
	@param b_flat                         �Ƿ�ȥƽ����λ��Ĭ���ǣ�
	@param b_normalize                    Э��������Ƿ��һ����Ĭ���ǣ�
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
	/*@brief SARͼ���ջʱ�ջ��߷ֲ�����
	* @param SLCH5Files                SARͼ�������ļ�
	* @param reference                 �ο�ͼ�����
	* @param temporal                  ʱ����ߣ�����ֵ,1��n����λ��day��
	* @param spatial                   �ռ���ߣ�����ֵ,1��n����λ��m��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int spatialTemporalBaselineEstimation(
		vector<string>& SLCH5Files,
		int reference,
		Mat& temporal,
		Mat& spatial
	);
	/** @brief ���������������delaunay��������
	
	@param nodes                       Delaunay��������ڵ�����
	@param edges                       Delaunay��������߽ṹ������
	@param start_edge                  ������ʼ����ţ���1��ʼ��
	@param distance_thresh             �߳���ֵ����������ֵ��ͨ���˱߻���
	@param quality_thresh              ������ֵ�����ڴ���ֵ��ͨ���˱߻���
	@return �ɹ�����0�����򷵻�-1
	*/
	int unwrap_region_growing(
		vector<tri_node>& nodes,
		const vector<tri_edge>& edges,
		size_t start_edge,
		double distance_thresh,
		double quality_thresh
	);
	/*@brief ����ͼ��Ĵ�С������ƫ���Լ�����-->��γ�ȵ�ת��ϵ��������ͼ��ĵ���߽磨�����С��γ�ȣ�
	* @param lat_coefficient                        ��������ת��ϵ��������-->γ�ȣ�
	* @param lon_coefficient                        ��������ת��ϵ��������-->���ȣ�
	* @param sceneHeight                            �����߶�
	* @param sceneWidth                             �������
	* @param offset_row                             ������ԭͼ���е���ƫ����
	* @param offset_col                             ������ԭͼ���е���ƫ����
	* @param lonMax                                 ��󾭶ȣ�����ֵ��
	* @param latMax                                 ���γ�ȣ�����ֵ��
	* @param lonMin                                 ��С���ȣ�����ֵ��
	* @param latMin                                 ��Сγ�ȣ�����ֵ��
	* @return �ɹ�����0�����򷵻�-1
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
	/*@brief ����ͼ���Ľǵ㾭γ�ȣ�����ͼ��ĵ���߽磨�����С��γ�ȣ�
	@param topleft_lon                             ���ϽǾ���
	@param topleft_lat                             ���Ͻ�γ��
	@param topright_lon                            ���ϽǾ���
	@param topright_lat                            ���Ͻ�γ��
	@param bottomleft_lon                          ���½Ǿ���
	@param bottomleft_lat                          ���½�γ��
	@param bottomright_lon                         ���½Ǿ���
	@param bottomright_lat                         ���½�γ��
	@param lonMax                                  ��󾭶ȣ�����ֵ��
	@param latMax                                  ���γ�ȣ�����ֵ��
	@param lonMin                                  ��С���ȣ�����ֵ��
	@param latMin                                  ��Сγ�ȣ�����ֵ��
	@return �ɹ�����0�����򷵻�-1
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
	/*@brief ���ݵ���߽���Ϣ��ȡSRTM�߳�
	* @param filepath                     ���ص�SRTM�߳��ļ�����·��
	* @param DEM_out                      DEM���ݣ�����ֵ��short�ͣ�
	* @param lonUpperLeft                 ���ϽǾ��ȣ�����ֵ��
	* @param latUpperLeft                 ���Ͻ�γ�ȣ�����ֵ��
	* @param lonMin                       ��С����
	* @param lonMax                       ��󾭶�
	* @param latMin                       ��Сγ��
	* @param latMax                       ���γ��
	* @return �ɹ�����0�����򷵻�-1
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
	/*@brief ���ݵ���߽���Ϣ�����������ص�SRTM�߳��ļ���
	* @param lonMin                       ��С����
	* @param lonMax                       ��󾭶�
	* @param latMin                       ��Сγ��
	* @param latMax                       ���γ��
	* @param name                         �ļ���
	* @return �ɹ�����0�����򷵻�-1
	*/
	static int getSRTMFileName(
		double lonMin,
		double lonMax,
		double latMin,
		double latMax,
		vector<string>& name
	);
	/*@brief ����SRTM�߳�����
	* @param name                         �ļ���
	* @param DEMpath                      ����DEM�ļ�����·��
	* @return �ɹ�����0�����򷵻�-1
	*/
	static int downloadSRTM(const char* name, const char* DEMpath);
	/*@brief �����ĸ��Ǿ�γ�����꣬��ͼƬ���ӵ�Google Earth��
	* @param BottomLeft_lon                ���½Ǿ���
	* @param BottomLeft_lat                ���½�γ��
	* @param BottomRight_lon               ���½Ǿ���
	* @param BottomRight_lat               ���½�γ��
	* @param TopRight_lon                  ���ϽǾ���
	* @param TopRight_lat                  ���Ͻ�γ��
	* @param TopLeft_lon                   ���ϽǾ���
	* @param TopLeft_lat                   ���Ͻ�γ��
	* @param Reference_lon                 �ο��㾭��
	* @param Reference_lat                 �ο���γ��
	* @param image_file                    ͼ���ļ����������д���KML�ļ�����ͬһĿ¼�£�
	* @param KML_file                      ��д��KML�ļ���
	* @param Legend_file                   ͼ���ļ����������д���KML�ļ�����ͬһĿ¼�£�
	* @return �ɹ�����0�����򷵻�-1
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
	/*@brief ƴ���ڱ�һ��3���Ӵ�������λ
	* @param IW1_h5file                     �Ӵ�1������λh5�ļ�
	* @param IW2_h5file                     �Ӵ�2������λh5�ļ�
	* @param IW3_h5file                     �Ӵ�3������λh5�ļ�
	* @param merged_phase_h5file            ƴ�Ӻ������λh5�ļ�������д�룩
	* @return �ɹ�����0�����򷵻�-1
	*/
	int S1_subswath_merge(
		const char* IW1_h5file,
		const char* IW2_h5file,
		const char* IW3_h5file,
		const char* merged_phase_h5file
	);
	/*@brief ƴ���ڱ�һ��3���Ӵ����Ӹ�ͼ��
	* @param IW1_h5file                     �Ӵ�1���Ӹ�ͼ��h5�ļ�
	* @param IW2_h5file                     �Ӵ�2���Ӹ�ͼ��h5�ļ�
	* @param IW3_h5file                     �Ӵ�3���Ӹ�ͼ��h5�ļ�
	* @param merged_slc_h5file            ƴ�Ӻ��Ӹ�ͼ��h5�ļ�������д�룩
	* @return �ɹ�����0�����򷵻�-1
	*/
	int S1_subswath_merge_slc(
		const char* IW1_h5file,
		const char* IW2_h5file,
		const char* IW3_h5file,
		const char* merged_slc_h5file
	);
	/*@brief ƴ���ڱ�һ��ͬһ�������frame�ĸ�����λ
	* @param h5files                        ͬһ�Ӵ���ͬframe������λh5�����ļ�
	* @param merged_phase_h5                ƴ�Ӻ�ĸ�����λh5�ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int S1_frame_merge(
		vector<string>& h5files,
		const char* merged_phase_h5
	);
	/*@brief ƴ��ͬһ�������frame�ĵ��Ӹ�ͼ��
	* @param frame1_h5                         ��ƴ��frame1��h5�ļ�
	* @param frame2_h5                         ��ƴ��frame2��h5�ļ�
	* @param outframe_h5                       ƴ��frame��h5�ļ�������д�룩
	* @return �ɹ�����0�����򷵻�-1
	*/
	int S1_frame_merge(
		const char* frame1_h5,
		const char* frame2_h5,
		const char* outframe_h5
	);
	/*@brief ��λ������룺SARͼ������ϵ--->ī��������ϵ
	* @param mapped_lon                        ��λ��Ӧ�ľ���
	* @param mapped_lat                        ��λ��Ӧ��γ��
	* @param phase                             SARͼ��������λ
	* @param mapped_phase                      ī����������λ������ֵ��
	* @param interpolation_method              ��ֵ������0�����ٽ���ֵ��1��˫���Բ�ֵ��Ĭ��Ϊ���ٽ���ֵ��
	* @param lon_east                          ����ͼ�����Ե���ȣ�����ֵ��
	* @param lon_west                          ����ͼ��������Ե���ȣ�����ֵ��
	* @param lat_north                         ����ͼ�����Եγ�ȣ�����ֵ��
	* @param lat_south                         ����ͼ�����ϱ�Եγ�ȣ�����ֵ��
	* @return �ɹ�����0�����򷵻�-1
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
	/*@brief ��λ������룺SARͼ������ϵ--->ī��������ϵ
	* @param mapped_lon                        ��λ��Ӧ�ľ���
	* @param mapped_lat                        ��λ��Ӧ��γ��
	* @param phase                             SARͼ��������λ
	* @param mapped_phase                      ī����������λ������ֵ��
	* @param grid_size                         �����ࣨm��
	* @param interpolation_method              ��ֵ������0�����ٽ���ֵ��1��˫���Բ�ֵ��Ĭ��Ϊ���ٽ���ֵ��
	* @param lon_east                          ����ͼ�����Ե���ȣ�����ֵ��
	* @param lon_west                          ����ͼ��������Ե���ȣ�����ֵ��
	* @param lat_north                         ����ͼ�����Եγ�ȣ�����ֵ��
	* @param lat_south                         ����ͼ�����ϱ�Եγ�ȣ�����ֵ��
	* @return �ɹ�����0�����򷵻�-1
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
	/*@brief SLC��ͼ�������룺SARͼ������ϵ--->ī��������ϵ
	* @param mapped_lon                        SLC��Ӧ�ľ���
	* @param mapped_lat                        SLC��Ӧ��γ��
	* @param slc                               SARͼ������SLC
	* @param mapped_slc                        ī��������SLC������ֵ��
	* @param interpolation_method              ��ֵ������0�����ٽ���ֵ��1��˫���Բ�ֵ��Ĭ��Ϊ���ٽ���ֵ��
	* @param lon_east                          ����ͼ�����Ե���ȣ�����ֵ��
	* @param lon_west                          ����ͼ��������Ե���ȣ�����ֵ��
	* @param lat_north                         ����ͼ�����Եγ�ȣ�����ֵ��
	* @param lat_south                         ����ͼ�����ϱ�Եγ�ȣ�����ֵ��
	* @return �ɹ�����0�����򷵻�-1
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

	/*@brief �����Ʒ������룺SARͼ������ϵ--->ī��������ϵ
	* @param DEM84                        84����ϵDEM��short�;���
	* @param input                        �������Ʒ
	* @param mapped_resolution_x          ������Ʒ������ֱ��ʣ�m��
	* @param mapped_resolution_y          ������Ʒ�ϱ���ֱ��ʣ�m��
	* @param mapped_result                ���������������ֵ��
	* @param lon_upperleft                84����ϵDEM���ϽǾ���
	* @param lat_upperleft                84����ϵDEM���Ͻ�γ��
	* @param offset_row                   SARͼ����ԭ�����е���ƫ����
	* @param offset_col                   SARͼ����ԭ�����е���ƫ����
	* @param sceneHeight                  SARͼ�񳡾��߶�
	* @param sceneWidth                   SARͼ�񳡾����
	* @param prf                          SAR�����״������ظ�Ƶ��
	* @param rangeSpacing                 ��������������m��
	* @param wavelength                   ����
	* @param nearRangeTime                ���б��ʱ��
	* @param acquisitionStartTime         ��λ�������ʼʱ��
	* @param acquisitionStopTime          ��λ���������ʱ��
	* @param stateVector                  ���ǹ�����ݣ�δ��ֵ��
	* @param lon_spacing                  84����ϵDEM���Ȳ���������㣩
	* @param lat_spacing                  84����ϵDEMγ�Ȳ���������㣩
	* @param lon_east                     ����ͼ�����Ե���ȣ�����ֵ��
	* @param lon_west                     ����ͼ��������Ե���ȣ�����ֵ��
	* @param lat_north                    ����ͼ�����Եγ�ȣ�����ֵ��
	* @param lat_south                    ����ͼ�����ϱ�Եγ�ȣ�����ֵ��
	* @return �ɹ�����0�����򷵻�-1
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

	/*@brief ���Ӹ�ͼ�������룺SARͼ������ϵ--->ī��������ϵ
	* @param DEM84                        84����ϵDEM��short�;���
	* @param slc                          �����뵥�Ӹ�ͼ��
	* @param mapped_resolution_x          ������Ʒ������ֱ��ʣ�m��
	* @param mapped_resolution_y          ������Ʒ�ϱ���ֱ��ʣ�m��
	* @param mapped_slc                   ���������������ֵ��
	* @param lon_upperleft                84����ϵDEM���ϽǾ���
	* @param lat_upperleft                84����ϵDEM���Ͻ�γ��
	* @param offset_row                   SARͼ����ԭ�����е���ƫ����
	* @param offset_col                   SARͼ����ԭ�����е���ƫ����
	* @param sceneHeight                  SARͼ�񳡾��߶�
	* @param sceneWidth                   SARͼ�񳡾����
	* @param prf                          SAR�����״������ظ�Ƶ��
	* @param rangeSpacing                 ��������������m��
	* @param wavelength                   ����
	* @param nearRangeTime                ���б��ʱ��
	* @param acquisitionStartTime         ��λ�������ʼʱ��
	* @param acquisitionStopTime          ��λ���������ʱ��
	* @param stateVector                  ���ǹ�����ݣ�δ��ֵ��
	* @param lon_spacing                  84����ϵDEM���Ȳ���������㣩
	* @param lat_spacing                  84����ϵDEMγ�Ȳ���������㣩
	* @param interp_times                 84����ϵDEM��ֵ������Ĭ��ֵΪ10��
	* @param lon_east                     ����ͼ�����Ե���ȣ�����ֵ��
	* @param lon_west                     ����ͼ��������Ե���ȣ�����ֵ��
	* @param lat_north                    ����ͼ�����Եγ�ȣ�����ֵ��
	* @param lat_south                    ����ͼ�����ϱ�Եγ�ȣ�����ֵ��
	* @return �ɹ�����0�����򷵻�-1
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
	* @brief ���õ�����׼�����ļ���TropiSAR��.grille�ļ���������ī����ͶӰ��DTM��DSMͶӰ��SAR����ϵ
	* @param grille_file                       grille�����ļ�
	* @param DTM                               ��ͶӰ��DTM����DSM����
	* @param xllcorner                         DTM���Ͻ�UTM_x����
	* @param yllcorner                         DTM���Ͻ�UTM_y����
	* @param prior_DTM                         SAR����ϵ����DTM
	* @param mapped_DTM                        ͶӰ��SAR����ϵ��DTM
	* @param SAR_extent_x                      SAR����x���귶Χ(0~SAR_extent_x)
	* @param SAR_extent_y                      SAR����y���귶Χ(0~SAR_extent_y)
	* @return �ɹ�����0�����򷵻�-1
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
	* @brief ���õ�����׼�����ļ���TropiSAR��.grille�ļ�����WGS84����ϵ����γ�ߣ���DTM��DSMͶӰ��SAR����ϵ
	* @param grille_file                       grille�����ļ�
	* @param DTM                               ��ͶӰ��DTM����DSM����
	* @param lon_upleft                        DTM���ϽǾ���
	* @param lat_upleft                        DTM���Ͻ�γ��
	* @param lon_interval                      ���Ȳ������
	* @param lat_interval                      γ�Ȳ������
	* @param prior_DTM                         SAR����ϵ����DTM
	* @param mapped_DTM                        ͶӰ��SAR����ϵ��DTM
	* @param SAR_extent_x                      SAR����x���귶Χ(0~SAR_extent_x)
	* @param SAR_extent_y                      SAR����y���귶Χ(0~SAR_extent_y)
	* @return �ɹ�����0�����򷵻�-1
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
	* @brief ��ȡTropiSAR��.grille�ļ�
	* @param grille_file                       ����ȡ��grille�����ļ�
	* @param row_matrix                        ÿ�����������Ϣ
	* @param col_matrix                        ÿ�����������Ϣ
	* @param lon_matrix                        ÿ������ľ�����Ϣ
	* @param lat_matrix                        ÿ�������γ����Ϣ
	* @param height_vector                     ÿ������ĸ߶���Ϣ
	* @return �ɹ�����0�����򷵻�-1
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
	* @brief ����γ������ת��ΪUTM����
	* @param lon                                ����
	* @param lat                                γ��
	* @param UTM_X                              UTM X����
	* @param UTM_Y                              UTM Y����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int lonlat2utm(
		Mat lon,
		Mat lat,
		Mat& UTM_X,
		Mat& UTM_Y
	);
	/*
	* @brief ��LVIS 2�������ж�ȡDTM��DSM��Ϣ
	* @param LVIS2_filelist                     LVIS 2���ļ�
	* @param DTM                                LVIS DTM��Ϣ(����ֵ��n��1)
	* @param DSM                                LVIS DSM��Ϣ(RH100������ֵ��n��1)
	* @param RH100                              LVIS RH100��Ϣ(����ֵ��n��1)
	* @param RH95                               LVIS RH100��Ϣ(����ֵ��n��1)
	* @param lat                                LVIS γ����Ϣ(����ֵ��n��1)
	* @param lon                                LVIS ������Ϣ(����ֵ��n��1)
	* @return �ɹ�����0�����򷵻�-1
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
	* @brief ��DTM/DSM����ͶӰ��DLR F-SAR����ϵ
	* @param east_min                          F-SAR������Ե
	* @param north_min                         F-SAR������Ե
	* @param east_max                          F-SAR������Ե
	* @param north_max                         F-SAR������Ե
	* @param projection_zone                   UTM����
	* @param pixel_spacing                     �ο�DEM����������ף�
	* @param sr2geo_az                         �ο�DEM��SAR����ϵ�еķ�λ�������
	* @param sr2geo_rg                         �ο�DEM��SAR����ϵ�еľ����������
	* @param sr2geo_h_ref                      �ο�DEM�ĸ߶�
	* @param sr2geo3d_rg_o1                    3D�������ϵ��
	* @param sr2geo3d_rg_o2                    3D�������ϵ��
	* @param sr2geo3d_az_o1                    3D�������ϵ��
	* @param sr2geo3d_az_o2                    3D�������ϵ��
	* @param DTM/DSM                           ��ͶӰ��DTM/DSM
	* @param DTM_lon                           ��ͶӰDTM/DSM�ľ���
	* @param DTM_lat                           ��ͶӰDTM/DSM��γ��
	* @param mapped_slc_rg                     ͶӰ��DTM/DSM��SAR����ϵ�еľ��������꣨����ֵ��
	* @param mapped_slc_az                     ͶӰ��DTM/DSM��SAR����ϵ�еķ�λ�����꣨����ֵ��
	* @param mapped_h0                         �ο�DEM������ֵ����mapped_slc_rg��mapped_slc_azͬ�ߴ磩
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
	// ���ݾ�γ�Ȼ�ȡ���ˮ׼��߲�
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