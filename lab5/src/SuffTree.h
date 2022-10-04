#ifndef SUFF_TREE_SUFFTREE_H
#define SUFF_TREE_SUFFTREE_H

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <map>

/*!
 * Класс суффиксного дерева. Конструируется из строки.
 */
class TSuffixTree
{
public:
	explicit TSuffixTree(const std::string &s);

	std::string
	lexMinString(const size_t &n);

	~TSuffixTree() = default;
private:
	/*!
	 * структура ребра суффиксного дерева.
	 */
	struct TNode
	{
		int left; ///< номер первого символа в вершине
		std::shared_ptr<int> right; ///< указатель на последний символ в вершине
		std::map<char, std::shared_ptr<TNode> > children; ///< дети
		std::shared_ptr<TNode> suffixLink; ///< суффиксная ссылка
		int id; ///< номер суффикса

		/*!
		 * Конструктор внутренней вершины: номер суффикса равен -1
		 * @param start - левая граница
		 * @param end  - указатель на правую границу
		 * @param link - суффиксная ссылка (указатель на другую вершину)
		 */
		TNode(const int &start, std::shared_ptr<int> end, std::shared_ptr<TNode> link) : TNode(start,
																							   std::move(end),
																							   std::move(link),
																							   -1) {}
		/*!
		 * Конструктор листа
		 * @param start - левая граница
		 * @param end - указатель на правую границу
		 * @param link - суффиксная ссылка (указатель на другую вершину)
		 * @param num - номер суффикса
		 */
		TNode(const int &start, std::shared_ptr<int> end, std::shared_ptr<TNode> link, const int &num)
			: left(start), right(std::move(end)), suffixLink(std::move(link)), id(num) {}

		/*!
		 * Функция подсчета листьев у вершины
		 * @param vec - вектор с номерами индексов листьев
		 */
		void
		countLeaves(std::vector<int> &vec)
		{
			for (auto [ch, child] : children)
			{
				child->countLeaves(vec);
			}
			if (this->id != -1)
			{
				vec.push_back(id);
			}
		}

		/*!
		 * Расчет длины строки, содержащейся в вершине
		 * @return длину подстроки, расположенную в вершине
		 */
		int
		length()
		{
			return *right - left + 1;
		}
	};

	void
	insert(const int &pos);

//	std::string
//	lexMinString(const size_t &n, const std::shared_ptr<TNode>& node);

	std::string text; ///< непосредственно строка

	std::shared_ptr<TNode> root; ///< корень
	std::shared_ptr<TNode> lastCreatedNode; ///< последняя созданная внутренняя вершина
	std::shared_ptr<TNode> activeNode; ///< вершина, с которой начнется расширение на следующей фазе
	int activeEdge; ///< индекс символа, задающий движение из текущей вершины
	int activeLength; ///< на сколько символом идем в направлении activeEdge
	int suffixCount; ///< сколько суффиксов осталось создать
	std::shared_ptr<int> leafEnd; ///< глобальная переменная, отвечающая за правую границу листьев
	const char SENTINEL = std::max('z', 'Z') + 1;
};
#endif //SUFF_TREE_SUFFTREE_H
