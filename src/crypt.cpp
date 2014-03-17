#define	BUILDING_NODE_EXTENSION	1
#include <node.h>
#include <unistd.h>

using namespace v8;


Handle<Value> CryptHash(const Arguments& args) {
	HandleScope scope;

	String::Utf8Value key(args[0]->ToString());
	String::Utf8Value salt(args[1]->ToString());

	char *hash = crypt(*key, *salt);

	return scope.Close(hash ? String::New(hash) : Undefined());
}

void ModuleInit(Handle<Object> exports, Handle<Object> module) {
	module->Set(String::NewSymbol("exports"),
	    FunctionTemplate::New(CryptHash)->GetFunction());
}

NODE_MODULE(crypt, ModuleInit)
