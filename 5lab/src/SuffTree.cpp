#include "SuffTree.h"

/*!
 * Конструктор суффиксного дерева для строки s
 * @param s - исходная строка
 */
TSuffixTree::TSuffixTree(const std::string &s) :
	text(s), activeEdge(-1), activeLength(0), suffixCount(0), leafEnd(std::make_shared<int>(-1)), lastCreatedNode(nullptr)
{
	text += SENTINEL;
	root = std::make_shared<TNode>(-1, std::make_shared<int>(-1), nullptr);
	activeNode = root;
	for (int i = 0; i < text.size(); ++i)
	{
		insert(i);
	}
}
std::string
TSuffixTree::lexMinString(const size_t &n)
{
	int remainder = static_cast<int>(n);
	std::string ans;
	auto node = root->children.begin()->second;
	while (ans.size() != n){
		int len = node->length();
		if (len > remainder){
			ans += text.substr(node->left, remainder);
		} else{
			ans += text.substr(node->left, len);
			remainder -= len;
			node = node->children.begin()->second;
		}
	}
	return ans;
}

/*!
 * Функция вставки суффикса, начинающегося в позиции pos
 * @param pos - позиция начала суффикса (0-индексация)
 */
void
TSuffixTree::insert(const int &pos)
{
	// установить lastCreatedInternalNode = null перед началом каждой фазы
	lastCreatedNode = nullptr;

	// глобальный end для листьев
	// инкремент leafEnd воплощает правило 1, прием 3: наращивание листьев
	++(*leafEnd);

	// сколько суффиксов осталось создать
	suffixCount++;

	while (suffixCount > 0)
	{
		// если activeLength равна 0, тогда ищем текущий символ из корня
		if (activeLength == 0)
			activeEdge = pos; // индекс текущего символа в тексте определяет дугу, по которой будем двигаться

		// ищем текущий символ в начале исходящих из activeNode дуг
		auto find = activeNode->children.find(text[activeEdge]);
		if (find == activeNode->children.end())
		{
			// если не нашли, то добавляем лист
			activeNode->children.emplace(text[activeEdge],
										 std::make_shared<TNode>(pos,
																 leafEnd, root,
																 pos - suffixCount + 1));

			// и коль скоро создали новую внутр. вершину, установим на нее суффиксную ссылку последней созданной внутренней вершины
			if (lastCreatedNode != nullptr)
			{
				lastCreatedNode->suffixLink = activeNode;
				lastCreatedNode = nullptr;
			}
		}
		else
		{
			// а если-таки есть дуга из activeNode, начинающаяся текущим символом, пойдем по ней спускаться
			auto next = find->second;
			int edgeLength = next->length();
			// спускаемся по дугам
			if (activeLength >= edgeLength)
			{
				activeEdge += edgeLength;
				activeLength -= edgeLength;
				activeNode = next;
				continue;
				// таким образом мы будем спускаться, покуда не станет activeLength < edgeLength
			}
			// правило 3: если текущий символ есть на дуге,
			// т.е. суффикс уже есть в дереве, то просто увеличим activeLength
			// как бы "шагнем вперед" по дуге
			if (text[next->left + activeLength] == text[pos])
			{
				// если lastCreatedInternalNode != null
				// это означает, что 2-е правило было применено ранее (создание новой вн. вершины)
				// установим суффиксную ссылку в activeNode
				if (lastCreatedNode != nullptr and activeNode != root)
				{
					lastCreatedNode->suffixLink = activeNode;
				}
				++activeLength;
				break;
			}
			// сюда попали, если текущего символа нет на дуге
			// создадим новую внутреннюю вершинку
			auto
				split = std::make_shared<TNode>(next->left, std::make_shared<int>(next->left + activeLength - 1), root);
			activeNode->children[text[activeEdge]] = split;
			// у "следующей" вершинки изменим, очевидно, начало, ибо мы ее "обрубили"
			next->left += activeLength;
			// подвесим новую листовую вершинку
			split->children.emplace(text[pos],
									std::make_shared<TNode>(pos,
															leafEnd,
															root,
															pos - suffixCount + 1));
			// подвесим отрубленную вершину
			split->children.emplace(text[next->left], next);
			// и не забудем про установку ссылок при создании новой внутренней вершины
			if (lastCreatedNode != nullptr)
			{
				lastCreatedNode->suffixLink = split;
			}
			lastCreatedNode = split;
		}
		--suffixCount;
		// если activeNode == root, тогда согласно правилу 2, мы декр. activeLength и инкр. activeEdge
		// это, можно сказать, альтернатива суфф. ссылке в случае, когда activeNode == root
		if (activeNode == root && activeLength > 0)
		{
			activeLength--;
			activeEdge++;
		}
		else if (activeNode != root) // если же activeNode != root, то радостно скачем по имеющейся суффиксной ссылке
		{
			activeNode = activeNode->suffixLink;
		}
	}
}

//std::string
//TSuffixTree::lexMinString(const size_t &n, const std::shared_ptr<TNode>& node)
//{
//	// конец рекурсии
//	if (n == 0){
//		return {};
//	}
//	int len = node->length();
//	if (len > n){
//		return text.substr(node->left, n);
//	} else {
//		return text.substr(node->left, len) + lexMinString(n - len, node->children.begin()->second);
//	}
//}
