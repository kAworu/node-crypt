#define	BUILDING_NODE_EXTENSION	1
#include <node.h>
#include <unistd.h>

using namespace v8;


Handle<Value> CryptHash(const Arguments& args) {
	HandleScope scope;

	if (args.Length() < 2) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}

	Local<String> key  = args[0]->ToString();
	Local<String> salt = args[1]->ToString();

	char *c_key  = new char[key->Length() + 1];
	char *c_salt = new char[salt->Length() + 1];
	key->WriteAscii(c_key);
	salt->WriteAscii(c_salt);
	char *hash = crypt(c_key, c_salt);
	delete[] c_key;
	delete[] c_salt;

	return scope.Close(hash ? String::New(hash) : Undefined());
}

void ModuleInit(Handle<Object> exports, Handle<Object> module) {
	module->Set(String::NewSymbol("exports"),
	    FunctionTemplate::New(CryptHash)->GetFunction());
}

NODE_MODULE(crypt, ModuleInit)
