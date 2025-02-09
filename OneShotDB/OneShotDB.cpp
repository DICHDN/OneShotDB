#include <map>
#include <string>
#include <iostream>
#include <memory>

class VeryHeavyDatabase
{
public:
	std::string GetData(const std::string& key) const noexcept
	{
		return "Very Big Data String: " + key;
	};

};
class CacheProxyDB : VeryHeavyDatabase
{
public:
	CacheProxyDB(std::unique_ptr<VeryHeavyDatabase> real_object) : real_db(move(real_object)) {}
	std::string GetData(const std::string& key)
	{
		if (cache_db.find(key) == cache_db.end())
		{
			std::cout << "Get data from real Database " << std::endl;
			cache_db[key] = real_db->GetData(key);
		}
		else
		{
			std::cout << "Get data from cache " << std::endl;
		}
	}

private:
	std::map<std::string, std::string> cache_db;
	std::unique_ptr<VeryHeavyDatabase> real_db;

};

class OneShotDB : VeryHeavyDatabase
{
public:
	explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1)
		: real_db(real_object), remaining_shots(shots) {
	}

	std::string GetData(const std::string& key) {
		if (remaining_shots > 0) {
			--remaining_shots;
			return real_db->GetData(key);
		}
		else {
			return "error";
		}
	}
private:
	VeryHeavyDatabase* real_db;
	size_t remaining_shots;
};

std::unique_ptr<CacheProxyDB> initCache()
{
	auto OriginalDB = std::make_unique<VeryHeavyDatabase>();
	return make_unique<CacheProxyDB>(move(OriginalDB));
}

int main()
{
	auto real_db = VeryHeavyDatabase();
	auto limit_db = OneShotDB(std::addressof(real_db), 2);
	std::cout << limit_db.GetData("key") << std::endl;
	std::cout << limit_db.GetData("key") << std::endl;
	std::cout << limit_db.GetData("key") << std::endl;
}